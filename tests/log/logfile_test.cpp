#include "../../include/log/LogFile.h"
#include "../../include/log/Logger.h"
#include <cstring>
#include <iostream>
#include <memory>

using namespace std;
using namespace logx;

std::unique_ptr<logx::LogFile> g_logFile;

void outputFunc(const char *msg, int len) { g_logFile->append(msg, len); }

void flushFunc() { g_logFile->flush(); }

int main() {
    char name[256] = {'\0'};
    strncpy(name, "logfile_test", sizeof(name) - 1);
    g_logFile.reset(new logx::LogFile(::basename(name), 200 * 1000));

    logx::Logger::setOutput(outputFunc);
    logx::Logger::setFlush(flushFunc);

    std::string line = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

    for (int i = 0; i < 5; i++) {
        LOG_INFO << line << i;
    }
    for (int i = 0; i < 5; i++) {
        LOG_ERROR << line << i;
    }

    return 0;
}