#include "qtoifuiedithandler.h"

// Finishes setting internal objects and pointers. Should be called right after the code that creates this object finishes setting pointers.
void qtOifUiEditHandler::setup() {
    linux_serial_output.ioif_manager = ioif_manager;
}

// Finds and triggers the appropriate edit dialog for the selected output interface
void qtOifUiEditHandler::editOutput(int row) {
    // Prevent other functions from editing the output interface list while we're searching through it
    std::lock_guard<std::mutex> lock(ioif_manager->oif_lock);
    // Abort if row is out of range
    if (row<0 || row>=ioif_manager->oif_list.size()) {
        printf("Attempted to edit an output interface that doesn't exist.\n");
        return;
    }

    // Get ID and attributes of the output interface we're gonna edit
    int type = ioif_manager->oif_list[row]->type;
    int id = ioif_manager->oif_list[row]->id;
    ioif_attr attributes = ioif_manager->oif_list[row]->attributes;
    // Show appropriate dialog for this output interface
    switch (type) {
#ifdef __linux__
    case IOIFTYPE_LINUXSERIALOUTPUT:
        linux_serial_output.trigger(id, attributes);
        break;
#endif
    }
}

// Finds and triggers the appropriate new item dialog for the selected output interface type
void qtOifUiEditHandler::addOutput(int type) {
    // Abort if type given doesn't exist
    if (type<0 || type>=ioif_manager->avail_oif.size()) {
        printf("Invalid interface type with index %i\n",type);
        return;
    }

    // Find actual interface type number from available output interface list
    int actual_type = ioif_manager->avail_oif[type].first;
    // Show appropriate dialog for this output interface
    switch (actual_type) {
#ifdef __linux__
    case IOIFTYPE_LINUXSERIALOUTPUT:
        linux_serial_output.trigger(-1, ioif_attr());
        break;
#endif
    }
}
