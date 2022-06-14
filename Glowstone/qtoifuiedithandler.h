#ifndef QTOIFUIEDITHANDLER_H
#define QTOIFUIEDITHANDLER_H

#include <ioifmanager.h>
#include <qteditlinuxserialoutput.h>

#include <map>

class qtOifUiEditHandler {
public:
    void setup();
    void editOutput(int id);
    void addOutput(int type);
    ioifManager * ioif_manager;
    qtEditLinuxSerialOutput linux_serial_output;
private:
};

#endif // QTOIFUIEDITHANDLER_H
