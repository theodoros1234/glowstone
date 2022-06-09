#include "qtnewoutputdialog.h"
#include "ui_newoutputdialog.h"

// Constructor
qtNewOutputDialog::qtNewOutputDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NewOutputDialog) {
    ui->setupUi(this);
}

// Destructor
qtNewOutputDialog::~qtNewOutputDialog() {
    delete ui;
}

// Populates list with available output interface types
void qtNewOutputDialog::populate(std::vector<std::pair<int, const char *> > &devlist) {
    for (auto item:devlist)
        ui->list->addItem(item.second);
}

// Slot for when "OK" button is pressed
void qtNewOutputDialog::on_buttonBox_accepted() {
    // Asks Output Interface Edit Handler to find the appropriate dialog for the selected interface
    oif_edit_handler->edit(nullptr, ui->list->currentRow());
}
