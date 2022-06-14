#include "qtmainwindow.h"
#include "ui_qtmainwindow.h"
#include "basetypes.h"

// Constructor
qtMainWindow::qtMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

// Destructor
qtMainWindow::~qtMainWindow() {
    delete ui;
}

// Finishes setting internal objects and pointers. Should be called right after the code that creates this object finishes setting pointers.
void qtMainWindow::setup() {
    // Passes pointers to interface managers and handlers to children
    oif_edit_handler.ioif_manager = ioif_manager;
    new_output_dialog.oif_edit_handler = &oif_edit_handler;

    new_output_dialog.populate(ioif_manager->avail_oif); // Populates new item dialogs
    oif_edit_handler.setup(); // Sets up output interface edit handler, since we finished setting its pointers.
    show(); // Shows window
}

// When the user clicks the add output button, it shows the new output dialog.
void qtMainWindow::on_outputAddButton_clicked() {
    new_output_dialog.show();
}

// When the user clicks the remove output button, it removes the currently selected output.
void qtMainWindow::on_outputRemoveButton_clicked() {
    ioif_manager->removeOutput(ui->outputList->currentRow());
    // Disable extra buttons on Output tab
    outputButtonsSetEnabled(false);
}

// Adds new item to output list
void qtMainWindow::addOutput(std::string name, std::string info) {
    std::string final_label = name + "\n" + info; // Create label name
    //int pos = ui->outputList->count(); // Find position of list it will be placed in
    ui->outputList->addItem(final_label.c_str()); // Places label in list

    /* This code was meant to create an icon that shows the currently displayed color.
    QListWidgetItem * item = ui->outputList->item(pos); // Gets pointer to item we just added to the list
    int s = item->sizeHint().height(); // Gets size of list item that was created
    QIcon icon(QPixmap(s, s)); // Creates icon based on the size we previously got
    output_list_painters.emplace_back(); // Creates painter for this icon's pixmap
    output_list_painters[pos] = new QPainter();
    icon.paint(output_list_painters[pos], 0, 0, s, s); // Paints icon
    item->setIcon(icon); // Sets the pixmap as an icon for the item we added to the list
    */
}

// Edits item in output list
void qtMainWindow::editOutput(int row, std::string name, std::string info) {
    ui->outputList->item(row)->setText((name+"\n"+info).c_str());
}

// Removes item from output list
void qtMainWindow::removeOutput(int row) {
    delete ui->outputList->takeItem(row);
}

// Activate extra buttons on Output tab when an output is selected, or deactivate them when all outputs are removed.
void qtMainWindow::on_outputList_itemSelectionChanged() {
    outputButtonsSetEnabled(true);
}

void qtMainWindow::outputButtonsSetEnabled(bool state) {
    ui->outputEditButton->setEnabled(state);
    ui->outputActivateButton->setEnabled(state);
    ui->outputRemoveButton->setEnabled(state);
}

void qtMainWindow::on_outputEditButton_clicked() {
    oif_edit_handler.editOutput(ui->outputList->currentRow());
}

