#include "uiabstractionlayer.h"

// Passes pointers to children and calls their setup functions
void uiAbstractionLayer::setup() {
    ioif_manager->ui_msg_pipe = &ioif_msg_pipe;
    qtUi.ioif_manager = ioif_manager;
    qtUi.setup();
    // Starts thread that listens for commands from ioifmanager
    ioif_msg_pipe_listener = std::thread(&uiAbstractionLayer::cmdListener, this);
}

// Adds new output to list
void uiAbstractionLayer::addOutput(std::string name, std::string info) {
    qtUi.addOutput(name, info);
}

// Edits output on list
void uiAbstractionLayer::editOutput(int row, std::string name, std::string info) {
    qtUi.editOutput(row, name, info);
}

// Removes output from list
void uiAbstractionLayer::removeOutput(int row) {
    qtUi.removeOutput(row);
}

// Listens for commands from message pipe connected to ioif_manager
void uiAbstractionLayer::cmdListener() {
    std::unique_lock lock(ioif_msg_pipe.mutex);
    while (true) {
        // Execute each command in queue
        while (!ioif_msg_pipe.cmd_queue.empty()) {
            // Read command
            ioifuiPipe::cmd cmd = ioif_msg_pipe.cmd_queue.front();
            ioif_msg_pipe.cmd_queue.pop();

            // Execute command
            switch (cmd.type) {
            case IOIFUIPIPE_CMD_ADDOUTPUT:
                addOutput(cmd.params[0], cmd.params[1]);
                break;
            case IOIFUIPIPE_CMD_EDITOUTPUT:
                editOutput(std::stoi(cmd.params[0]), cmd.params[1], cmd.params[2]);
                break;
            case IOIFUIPIPE_CMD_REMOVEOUTPUT:
                removeOutput(std::stoi(cmd.params[0]));
                break;
            default:
                // Print an error message when an invalid command is received
                printf("Invalid command transferred through IOIFManager->UiAbstractionLayer pipe: type=%i, params=[", cmd.type);
                for (auto i : cmd.params)
                    printf("\"%s\",", i.c_str());
                printf("]\n");
            }
        }
        // Unlock and wait for a notification
        ioif_msg_pipe.cn_var.wait(lock);
    }
}
