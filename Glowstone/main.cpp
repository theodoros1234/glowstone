#include "uiabstractionlayer.h"
#include "basetypes.h"
#include "linuxserialoutput.h"
#include "ioifmanager.h"

#include <vector>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    uiAbstractionLayer ui;
    ioifManager ioif_manager;

    // Connects objects between each other, where needed
    ui.ioif_manager = &ioif_manager;
    //ioif_manager.ui = &ui;

    // Sets up objects, since we finished setting their pointers.
    ui.setup();
    //window.addOutput("/dev/ttyACM0 (active)","Linux Serial Output, 115200 baud");

    return app.exec();
}
