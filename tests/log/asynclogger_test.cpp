#include "../../include/log/AsyncLogger.h"
#include "../../include/log/Logger.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

off_t kRollSize = 10 * 1000 * 1000;

logx::AsyncLogger *g_asyncLog = NULL;

void asyncOutput(const char *msg, int len) { g_asyncLog->append(msg, len); }

void test_asynclogger(char *argv[]) {
    char name[256] = {'\0'};
    strncpy(name, argv[0], sizeof name - 1);

    logx::AsyncLogger log(::basename(name), kRollSize);
    g_asyncLog = &log;
    log.start();

    logx::Logger::setOutput(asyncOutput);
    for (int i = 0; i < 10; i++) {
        LOG_INFO << "Hello 0123456789"
                 << " abcdefghijklmnopqrstuvwxyz ";
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main(int argc, char *argv[]) {
    test_asynclogger(argv);

    return 0;
}
