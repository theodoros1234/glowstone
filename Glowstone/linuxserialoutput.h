#define IOIFTYPE_LINUXSERIALOUTPUT 1
#ifndef LINUXSERIALOUTPUT_H
#define LINUXSERIALOUTPUT_H
#ifdef __linux__

#include "baseoutputinterface.h"

#include <stdio.h>
#include <cstring>
#include <string>
#include <mutex>

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

class linuxSerialOutput : public BaseOutputInterface {
public:
    const std::string if_type = "linuxSerialOutput";

    linuxSerialOutput(int id, ioif_attr attributes);
    ~linuxSerialOutput();
    void activate();
    void deactivate(int reason = DEACTIVATE_REASON_NONE);
    void setMode(char m);
    void setColor(color_t c);
private:
    int serial_port, baud_rate;
    char * path;

    void deactivate_internal(int reason = DEACTIVATE_REASON_NONE);
    int connect();
    void setError(int errnum);
    struct termios tty;
};

#endif // __linux__
#endif // LINUXSERIALOUTPUT_H
