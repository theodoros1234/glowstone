#include "ioifuipipe.h"

ioifuiPipe::ioifuiPipe() {}

void ioifuiPipe::sendCmd(int type, std::vector<std::string> params) {
    {
        std::lock_guard lock(mutex);
        cmd_queue.emplace(type, params);
    }
    cn_var.notify_one();
}
