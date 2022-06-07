#ifndef OIFUIEDITHANDLER_H
#define OIFUIEDITHANDLER_H

#include <ioifmanager.h>
#include <editlinuxserialoutput.h>

class oifUiEditHandler {
public:
    void setup();
    void edit(void * item, int type);
    ioifManager * ioif_manager;
    EditLinuxSerialOutput linux_serial_output;
};

#endif // OIFUIEDITHANDLER_H
