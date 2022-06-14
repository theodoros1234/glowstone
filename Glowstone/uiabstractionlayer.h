#ifndef UIABSTRACTIONLAYER_H
#define UIABSTRACTIONLAYER_H

#include "basetypes.h"
#include "qtmainwindow.h"
#include "ioifmanager.h"
#include "ioifuipipe.h"

#include <string>
#include <thread>

class uiAbstractionLayer {
public:
    void setup();
    void addOutput(std::string name, std::string info);
    void editOutput(int row, std::string name, std::string info);
    void removeOutput(int row);
    void cmdListener();

    ioifManager * ioif_manager;
    ioifuiPipe ioif_msg_pipe;
private:
    std::thread ioif_msg_pipe_listener;
    qtMainWindow qtUi;
};

#endif // UIABSTRACTIONLAYER_H
