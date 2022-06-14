#ifndef BASEOUTPUTINTERFACE_H
#define BASEOUTPUTINTERFACE_H
#define OIFSTATE_INACTIVE 0
#define OIFSTATE_ACTIVE 1
#define OIFSTATE_ERROR 2
#define OIFSTATE_STARTING 3
#define OIFSTATE_STOPPING 4
#define DEACTIVATE_REASON_NONE 0
#define DEACTIVATE_REASON_ERROR 1

#include "basetypes.h"

#include <string>
#include <mutex>
#include <map>

class BaseInputInterface;

class BaseOutputInterface {
public:
    int id=-1, type=-1;
    char * error_str = nullptr;
    char mode = '\0';
    struct color_t color;
    int state = OIFSTATE_INACTIVE;
    std::map<std::string, std::string> attributes;
    //std::vector<inputInterface*> attached_iif;

    virtual void activate();
    virtual void deactivate(int reason = DEACTIVATE_REASON_NONE);
    virtual void setMode(char m);
    virtual void setColor(color_t c);
    virtual ~BaseOutputInterface();
    void attachIIF(BaseInputInterface * iif);
    void detachIIF(BaseInputInterface * iif);
protected:
    std::mutex lock;
};

#endif // BASEOUTPUTINTERFACE_H
