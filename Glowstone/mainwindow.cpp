#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basetypes.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

// Destructor
MainWindow::~MainWindow() {
    delete ui;
}

// Finishes setting internal objects and pointers. Should be called right after the code that creates this object finishes setting pointers.
void MainWindow::setup() {
    // Passes pointers to interface managers and handlers to children
    oif_edit_handler.ioif_manager = ioif_manager;
    new_output_dialog.oif_edit_handler = &oif_edit_handler;

    new_output_dialog.populate(ioif_manager->avail_oif); // Populates new item dialogs
    oif_edit_handler.setup(); // Sets up output interface edit handler, since we finished setting its pointers.
}

// When the user clicks the add output button, it shows the new output dialog.
void MainWindow::on_outputAddButton_clicked() {
    new_output_dialog.show();
}

// Adds new item to output list
void MainWindow::addOutput(std::string name, std::string info) {
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
