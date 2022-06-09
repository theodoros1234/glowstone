#include "qteditlinuxserialoutput.h"
#include "ui_editlinuxserialoutput.h"

#include <string>

// Constructor
qtEditLinuxSerialOutput::qtEditLinuxSerialOutput(QWidget *parent) : QDialog(parent), ui(new Ui::EditLinuxSerialOutput) {
    ui->setupUi(this);
}

// Destructor
qtEditLinuxSerialOutput::~qtEditLinuxSerialOutput() {
    delete ui;
}

// Function to call when this dialog needs to be shown. Configures UI to match item being edited/added.
void qtEditLinuxSerialOutput::trigger(linuxSerialOutput * item) {
    std::string path;
    std::string title;
    int baud_rate = 115200;

    // Create title string, depending on if we're creating or editing an item
    // Also, fetch any other properties from the interface to display
    if (item == nullptr) {
        title = "New ";
        title += std::string(ioif_manager->ifName(IOIFTYPE_LINUXSERIALOUTPUT));
    } else {
        title = "Edit ";
        path = std::string(item->path);
        baud_rate = item->baud_rate;
        title += path;
    }
    // Set title
    setWindowTitle(title.c_str());
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

    // Clear list
    ui->list->clear();

    // Scan /dev/ directory for devices
    for (auto const& dir_entry : std::filesystem::directory_iterator{devpath}){
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
            ui->list->addItem(path.c_str());
            // If this was the selected device for the item the user wants to edit, highlight it.
            if (selected_device == path)
                ui->list->setCurrentRow(ui->list->count()-1);
        }
    }
}
