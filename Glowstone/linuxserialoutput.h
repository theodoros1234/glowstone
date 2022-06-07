#ifdef __linux__
#ifndef LINUXSERIALOUTPUT_H
#define LINUXSERIALOUTPUT_H

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
    int baud_rate;

    linuxSerialOutput(std::string p, int b);
    ~linuxSerialOutput();
    void activate();
    void deactivate(int reason = DEACTIVATE_REASON_NONE);
    void setMode(char m);
    void setColor(color_t c);
    char * path;
private:
    int serial_port;
    std::mutex serial_port_mutex;

    int connect();
    void setError(int errnum);
    struct termios tty;
};

#endif // LINUXSERIALOUTPUT_H
#endif // __linux__
