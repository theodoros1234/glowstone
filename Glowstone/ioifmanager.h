#ifndef IOIFMANAGER_H
#define IOIFMANAGER_H

#define IOIF_UIEVENT_NEWITEM 0
#define IOIF_UIEVENT_DELITEM 1
#define IOIF_UIEVENT_EDTITEM 2
#define IOIF_UIEVENT_REFRESH 3

#include "baseoutputinterface.h"
#include "linuxserialoutput.h"
#include "ioifuipipe.h"
#include "basetypes.h"

#include <vector>
#include <string>
#include <mutex>
#include <map>

typedef std::pair<int,const char *> ifid;

class ioifManager {
public:
    ioifManager();
    const char * ifName(int type);
    void addOutput(int type, ioif_attr attributes);
    void editOutput(int id, ioif_attr attributes);
    void removeOutput(int row);

    std::vector<ifid> avail_oif;
    std::vector<BaseOutputInterface*> oif_list;
    std::mutex iif_lock, oif_lock;
    ioifuiPipe * ui_msg_pipe;
private:
    int id_itr = 0;
};

#endif // IOIFMANAGER_H
