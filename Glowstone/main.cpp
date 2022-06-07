#include "mainwindow.h"
#include "newoutputdialog.h"
#include "basetypes.h"
#include "linuxserialoutput.h"
#include "ioifmanager.h"

#include <vector>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    ioifManager ioif_manager;

    // Connects objects between each other, where needed
    window.ioif_manager = &ioif_manager;
    ioif_manager.gui = &window;

    // Sets up objects, since we finished setting their pointers.
    window.setup();
    //window.addOutput("/dev/ttyACM0 (active)","Linux Serial Output, 115200 baud");

    // Shows main window
    window.show();
    return app.exec();
}
