#include "ioifmanager.h"

ioifManager::ioifManager() {
    // Check which IO interface types are available
#ifdef LINUXSERIALOUTPUT_H
    avail_oif.emplace_back(IOIFTYPE_LINUXSERIALOUTPUT, "Linux Serial Output");
#endif
}

const char * ioifManager::ifName(int type) {
    for (auto interface : avail_oif)
        if (interface.first == type)
            return interface.second;
    return nullptr;
}
