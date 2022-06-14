#include "qteditlinuxserialoutput.h"
#include "ui_qteditlinuxserialoutput.h"
#include "linuxserialoutput.h"

#include <string>

// Constructor
qtEditLinuxSerialOutput::qtEditLinuxSerialOutput(QWidget *parent) : QDialog(parent), ui(new Ui::EditLinuxSerialOutput) {
    ui->setupUi(this);
    OKButton = ui->buttonBox->button(ui->buttonBox->Ok);
}

// Destructor
qtEditLinuxSerialOutput::~qtEditLinuxSerialOutput() {
    delete ui;
}

// Function to call when this dialog needs to be shown. Configures UI to match item being edited/added.
void qtEditLinuxSerialOutput::trigger(int id, ioif_attr attributes) {
    qtEditLinuxSerialOutput::id = id;
    int baud_rate = 115200;
    std::string path;
    std::string title;

    // Try to find the attributes we want, otherwise keep default values
    auto attr_itr = attributes.find("path");
    if (attr_itr != attributes.end())
        path = attr_itr->second;
    attr_itr = attributes.find("baud_rate");
    if (attr_itr != attributes.end())
        baud_rate = std::stoi(attr_itr->second);

    // Create title string, depending on if we're creating or editing an item
    // Also, fetch any other properties from the interface to display
    if (id == -1)
        title = "New " + std::string(ioif_manager->ifName(IOIFTYPE_LINUXSERIALOUTPUT));
    else
        title = "Edit " + path;
    // Set title
    setWindowTitle(title.c_str());
    // Set window file path attribute
    setWindowFilePath(path.c_str());
    // Populate device list
    scanForDevices(path);
    // Set baud rate
    ui->baudRate->setValue(baud_rate);
    // Show window
    show();
}

// Scans for serial devices and populates list shown in the UI
void qtEditLinuxSerialOutput::scanForDevices(std::string selected_device) {
    std::string path;
    // Array that contains prefixes that we consider to be valid for the serial devices we want to detect
    std::string accepted_prefixes[] = {
        "/dev/ttyUSB",
        "/dev/ttyACM"
    };
    bool selected_device_was_added = false;

    // Clear list
    ui->list->clear();
    list_entries.clear();

    // Scan /dev/ directory for devices
    for (auto const& dir_entry : std::filesystem::directory_iterator{devpath}) {
        path = dir_entry.path().string();
        bool full_match = false;
        // Filter out devices that don't match our prefix criteria
        for (auto prefix:accepted_prefixes) {
            bool matches = true;
            if (prefix.size() > path.size())
                continue;
            for (unsigned int i=0; i<prefix.size(); i++)
                if (prefix[i] != path[i]) {
                    matches = false;
                    break;
                }
            if (matches) {
                full_match = true;
                break;
            }
        }
        // If this device matched our criteria, add it to the list.
        if (full_match) {
            list_entries.push_back(path);
            ui->list->addItem(path.c_str());
            // If this was the selected device for the item the user wants to edit, highlight it.
            if (selected_device == path) {
                selected_device_was_added = true;
                ui->list->setCurrentRow(ui->list->count()-1);
            }
        }
    }
    // If selected device isn't currently connected, add it to the list now.
    if (!selected_device_was_added && !selected_device.empty()) {
        list_entries.push_back(selected_device);
        ui->list->addItem((selected_device+" (not connected)").c_str());
        ui->list->setCurrentRow(ui->list->count()-1);
        selected_device_was_added = true;
    }
    // Disable the OK button if nothing is selected
    OKButton->setEnabled(selected_device_was_added);
}

// Slot for when the OK button is pressed
void qtEditLinuxSerialOutput::on_EditLinuxSerialOutput_accepted() {
    ioif_attr attributes;
    // Get info set from UI
    attributes["path"] = list_entries[ui->list->currentRow()];
    attributes["baud_rate"] = std::to_string(ui->baudRate->value());

    if (id==-1) // If we're creating a new item
        ioif_manager->addOutput(IOIFTYPE_LINUXSERIALOUTPUT, attributes);
    else // If we're editing an existing item
        ioif_manager->editOutput(id, attributes);
}

// Enable OK button when something is selected
void qtEditLinuxSerialOutput::on_list_itemSelectionChanged() {
    OKButton->setEnabled(true);
}

