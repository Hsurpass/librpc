#include "../../include/log/Logger.h"
#include "../../include/utils/CurrentThread.h"
#include "../../include/utils/ThreadPool.h"

#include <functional>
#include <iostream>

using namespace std;

void longTask(int num) {
    LOG_INFO << "longTask " << num;
    utils::CurrentThread::sleepUsec(10000);
}

void test2() {
    LOG_WARN << "Test ThreadPool by stoping early.";
    utils::ThreadPool pool("ThreadPool");
    pool.setMaxQueueSize(5);
    pool.start(3);

    for (int i = 0; i < 10; ++i) {
        pool.addTask(std::bind(longTask, i));
        printf("[test2] thread1 i:%d\n", i);
    }

    utils::CurrentThread::sleepUsec(5000000);
    LOG_WARN << "stop pool";
    pool.stop(); // early stop
}

int main() {
    test2();

    return 0;
}
