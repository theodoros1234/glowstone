#include "ioifmanager.h"

ioifManager::ioifManager() {
    // Check which IO interface types are available
#ifdef LINUXSERIALOUTPUT_H
    avail_oif.emplace_back(IOIFTYPE_LINUXSERIALOUTPUT, "Linux Serial Output");
#endif
}

// Get pointer to character array with name of type
const char * ioifManager::ifName(int type) {
    for (auto interface : avail_oif)
        if (interface.first == type)
            return interface.second;
    return nullptr;
}

// Create a new output interface
void ioifManager::addOutput(int type, ioif_attr attributes) {
    // Make sure no other output is accessing output interfaces
    std::lock_guard output_lock(oif_lock);

    int id = id_itr++;
    BaseOutputInterface * oif_pointer;
    std::string title, info;

    // Find name of this type
    for (auto iftype:avail_oif)
        if (iftype.first == type) {
            info = std::string(iftype.second);
            break;
        }
    // Abort if type is invalid
    if (info.empty()) {
        printf("Attempted to create output interface of invalid/unavailable type.\n");
        return;
    }
    // Create the interface type we were instructed to
    switch (type) {
#ifdef __linux__
    case IOIFTYPE_LINUXSERIALOUTPUT:
        oif_pointer = new linuxSerialOutput(id, attributes);
        title = attributes["path"];
        info += ", " + attributes["baud_rate"] + " baud";
        break;
#endif
    }
    // Add a pointer to the interface to output list
    oif_list.push_back(oif_pointer);
    // Update UI
    ui_msg_pipe->sendCmd(IOIFUIPIPE_CMD_ADDOUTPUT, {title, info});
}

// Edit an output interface
void ioifManager::editOutput(int id, ioif_attr attributes) {
    // Make sure that no other output is accessing output interfaces
    std::lock_guard output_lock(oif_lock);
    // Find item in list by ID
    int row = -1;
    for (int i=0; i<oif_list.size(); i++)
        if (oif_list[i]->id == id) {
            row = i;
            break;
        }
    // Abort if item not found
    if (row == -1) {
        printf("Attempted to edit an output interface that doesn't exist.\n");
        return;
    }

    std::string title, info;
    // Get info about output interface
    int type = oif_list[row]->type;
    // Find name of this type
    for (auto iftype:avail_oif)
        if (iftype.first == type) {
            info = std::string(iftype.second);
            break;
        }
    // Abort if type is invalid
    if (info.empty()) {
        printf("Attempted to edit an output interface of invalid/unavailable type.\n");
        return;
    }
    // Deactivate and remove this output interface
    oif_list[row]->deactivate();
    delete oif_list[row];
    // Create a new output interface in the old one's place. Decide which type to create.
    switch (type) {
#ifdef __linux__
    case IOIFTYPE_LINUXSERIALOUTPUT:
        oif_list[row] = new linuxSerialOutput(id, attributes);
        title = attributes["path"];
        info += ", " + attributes["baud_rate"] + " baud";
        break;
#endif
    }
    // Update UI
    ui_msg_pipe->sendCmd(IOIFUIPIPE_CMD_EDITOUTPUT, {std::to_string(row), title, info});
}

// Remove an output interface
void ioifManager::removeOutput(int row) {
    // Make sure that no other output is accessing output interfaces
    std::lock_guard output_lock(oif_lock);
    // Abort if removing an output that doesn't exist
    if (row<0 || row>=oif_list.size()) {
        printf("Attempted to remove an output interface that doesn't exist.\n");
        return;
    }

    // Deactivate and remove this output interface
    oif_list[row]->deactivate();
    delete oif_list[row];
    oif_list.erase(oif_list.begin()+row);
    // Update UI
    ui_msg_pipe->sendCmd(IOIFUIPIPE_CMD_REMOVEOUTPUT, {std::to_string(row)});
}
