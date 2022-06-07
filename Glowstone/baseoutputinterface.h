#ifndef BASEOUTPUTINTERFACE_H
#define BASEOUTPUTINTERFACE_H
#define OIFSTATE_INACTIVE 0
#define OIFSTATE_ACTIVE 1
#define OIFSTATE_ERROR 2
#define OIFSTATE_STARTING 3
#define OIFSTATE_STOPPING 4
#define DEACTIVATE_REASON_NONE 0
#define DEACTIVATE_REASON_ERROR 1
#include <string>
#include <mutex>
#include "basetypes.h"

class BaseOutputInterface {
public:
    char * error_str = nullptr;
    char mode = '\0';
    struct color_t color;
    int state = OIFSTATE_INACTIVE;
    std::mutex state_change_mutex;
    //std::vector<inputInterface*> attached_iif;
};

#endif // BASEOUTPUTINTERFACE_H
