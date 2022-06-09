#include "qtoifuiedithandler.h"

// Finishes setting internal objects and pointers. Should be called right after the code that creates this object finishes setting pointers.
void qtOifUiEditHandler::setup() {
    linux_serial_output.ioif_manager = ioif_manager;
}

// Finds and triggers the appropriate edit dialog for the selected output interface type
void qtOifUiEditHandler::edit(void *item, int type) {
    int actual_type = ioif_manager->avail_oif[type].first;
    switch (actual_type) {
#ifdef LINUXSERIALOUTPUT_H
    case IOIFTYPE_LINUXSERIALOUTPUT:
        linux_serial_output.trigger((linuxSerialOutput*)item);
        break;
#endif
    }
}
