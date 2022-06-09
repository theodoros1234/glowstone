#ifndef QTOIFUIEDITHANDLER_H
#define QTOIFUIEDITHANDLER_H

#include <ioifmanager.h>
#include <qteditlinuxserialoutput.h>

class qtOifUiEditHandler {
public:
    void setup();
    void edit(void * item, int type);
    ioifManager * ioif_manager;
    qtEditLinuxSerialOutput linux_serial_output;
};

#endif // QTOIFUIEDITHANDLER_H
