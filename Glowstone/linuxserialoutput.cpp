#ifdef __linux__
#include "linuxserialoutput.h"

#include <stdio.h>
#include <cstring>
#include <string>
#include <mutex>

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

// Constructor
linuxSerialOutput::linuxSerialOutput(int id, ioif_attr attributes) {
    BaseOutputInterface::id = id;
    BaseOutputInterface::type = IOIFTYPE_LINUXSERIALOUTPUT;
    BaseOutputInterface::attributes = attributes;
    // Convert and store path as C string
    path = new char[attributes["path"].size()+1];
    std::strcpy(path, attributes["path"].c_str());
    // Store baud rate
    baud_rate = std::stoi(attributes["baud_rate"]);
    printf("Created new linux serial output interface '%s' %i baud.\n",path,baud_rate);
}

// Destructor
linuxSerialOutput::~linuxSerialOutput() {
    printf("Deleting linux serial output interface '%s'.\n",path);
    // Deactivate if active
    if (state==OIFSTATE_ACTIVE || state==OIFSTATE_STARTING)
        deactivate_internal();
    // Delete internal heap variables
    delete path;
}

// Connect to serial port
int linuxSerialOutput::connect() {
    printf("Connecting to serial port '%s'.\n",path);
    // Open serial port
    serial_port = open(path,O_RDWR);
    if (serial_port<0)
        return errno;
    // Get attributes of serial port
    printf("Configuring serial port...\n");
    if (tcgetattr(serial_port, &tty)!=0)
        return errno;

    // Set serial communication flags
    tty.c_lflag &= ~ICANON; // Disable canonical mode
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // Set baud rate
    cfsetispeed(&tty, baud_rate);
    cfsetospeed(&tty, baud_rate);

    // Save serial port attributes
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
        return errno;
    return 0;
}

// Activate module
void linuxSerialOutput::activate() {
    // Make sure no other activation/deactivation function is running.
    lock.lock();
    state = OIFSTATE_STARTING;
    // Try to connect to serial port
    int connect_errcode = connect();
    // If there's an error, store error message and stop.
    if (connect_errcode) {
        setError(connect_errcode);
        printf("Error opening serial port: %s\n",error_str);
        lock.unlock();
        deactivate(DEACTIVATE_REASON_ERROR);
        return;
    }
    // Otherwise, announce activation success
    printf("Linux serial output interface '%s' is ready to use.\n",path);
    state = OIFSTATE_ACTIVE;
    lock.unlock();
}

// Deactivate module
void linuxSerialOutput::deactivate(int reason) {
    deactivate_internal(reason);
}

void linuxSerialOutput::deactivate_internal(int reason) {
    // Make sure no other activation/deactivation function is running.
    std::lock_guard<std::mutex> state_lock(lock);
    if (state != OIFSTATE_ACTIVE && state != OIFSTATE_STARTING)
        return;
    state = OIFSTATE_STOPPING;
    printf("Deactivating linux serial output interface '%s'",path);
    // Close serial port
    close(serial_port);
    // State deactivation reason
    switch (reason) {
    case DEACTIVATE_REASON_ERROR:
        printf(" because an error occured.\n");
        state = OIFSTATE_ERROR;
        break;
    default:
        printf(".\n");
        state = OIFSTATE_INACTIVE;
    }
}

// Set error message based on error code
void linuxSerialOutput::setError(int errnum) {
    if (error_str!=nullptr)
        delete error_str;
    char * pointer = strerror(errnum);
    error_str = new char[sizeof(*pointer)/sizeof(char)]();
    strcpy(error_str,pointer);
}

// Set LED strip color mode
void linuxSerialOutput::setMode(char m) {
    std::lock_guard<std::mutex> guard(lock);
    mode = m;
    if (state==OIFSTATE_ACTIVE) {
        // Make sure no other function is currently sending data to serial port
        // Construct command string that will be sent to the connected Arduino
        char cmd[2] = {'$',m};
        // Send data
        write(serial_port, cmd, sizeof(cmd));
    }
}

// Set LED strip color value
void linuxSerialOutput::setColor(color_t c) {
    std::lock_guard<std::mutex> guard(lock);
    color = c;
    if (state==OIFSTATE_ACTIVE) {
        // Make sure no other function is currently sending data to serial port
        // Construct command string that will be sent to the connected Arduino
        char cmd[8];
        int cmd_length = 0;
        // Encode HEX values from color
        if (mode=='S')
            cmd_length += snprintf(cmd, 8, "#%02X%02X%02X", c.r, c.g, c.b);
        if (mode=='H')
            cmd_length += snprintf(cmd, 8, "#%02X", c.v);
        // Send data
        write(serial_port, cmd, cmd_length);
    }
}

#endif // __linux__
