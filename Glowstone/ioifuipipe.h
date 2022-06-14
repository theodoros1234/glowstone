#ifndef IOIFUIPIPE_H
#define IOIFUIPIPE_H

#include <mutex>
#include <queue>
#include <vector>
#include <string>
#include <condition_variable>

#define IOIFUIPIPE_CMD_ADDOUTPUT 1
#define IOIFUIPIPE_CMD_EDITOUTPUT 2
#define IOIFUIPIPE_CMD_REMOVEOUTPUT 3

class ioifuiPipe {
public:
    struct cmd {
        int type;
        std::vector<std::string> params;
        cmd(int type, std::vector<std::string> params) : type(type), params(params) {};
    };
    ioifuiPipe();
    void sendCmd(int type, std::vector<std::string> params);

    std::mutex mutex;
    std::condition_variable cn_var;
    std::queue<cmd> cmd_queue;
};

#endif // IOIFUIPIPE_H
