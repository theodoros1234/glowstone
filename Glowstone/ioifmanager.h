#ifndef IOIFMANAGER_H
#define IOIFMANAGER_H

#define IOIFTYPE_LINUXSERIALOUTPUT 1
#define IOIF_UIEVENT_NEWITEM 0
#define IOIF_UIEVENT_DELITEM 1
#define IOIF_UIEVENT_EDTITEM 2
#define IOIF_UIEVENT_REFRESH 3

#include "linuxserialoutput.h"
#include <vector>
#include <string>

//class MainWindow;

struct outputInterface {
    int type;
    void * point;
    outputInterface(int type, void * point) : type(type), point(point) {};
};

class ioifManager {
public:
    ioifManager();
    const char * ifName(int type);
    void addOutput(int type, void * point);

    std::vector< std::pair<int,const char *> > avail_oif;
    std::vector<outputInterface*> oif_list;

    //MainWindow * gui;
};

#endif // IOIFMANAGER_H
