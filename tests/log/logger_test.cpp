#include "../../include/log/LogFile.h"
#include "../../include/log/Logger.h"
#include "../../include/utils/TimeZone.h"

#include <iostream>
#include <stdio.h>
#include <thread>
#include <unistd.h>

using namespace std;

int g_total;
FILE *g_file;
std::unique_ptr<logx::LogFile> g_logFile;

void test_logx_logger() {
    logx::Logger::setLogLevel(logx::Logger::ERROR);

    LOG_TRACE << "trace";
    LOG_DEBUG << "debug";
    LOG_INFO << "Hello";
    LOG_WARN << "World";
    LOG_ERROR << "Error";
    LOG_SYSERR << "SYSERR";
    // LOG_SYSFATAL << "SYSFATAL";
    // LOG_FATAL << "FATAL";
    LOG_INFO << "sizeof(logx::Logger):" << sizeof(logx::Logger);
    LOG_INFO << "sizeof(logx::LogStream):" << sizeof(logx::LogStream);
    LOG_INFO << "sizeof(logx::Fmt):" << sizeof(logx::Fmt);
    LOG_INFO << "sizeof(logx::LogStream::Buffer): " << sizeof(logx::LogStream::Buffer);
}

void test_logger_TimeZone() {
    {
        g_file = stdout;
        sleep(1);
        utils::TimeZone::TimeZone beijing(8 * 3600, "CST");
        logx::Logger::setTimeZone(beijing);
        LOG_TRACE << "trace CST";
        LOG_DEBUG << "debug CST";
        LOG_INFO << "Hello CST";
        LOG_WARN << "World CST";
        LOG_ERROR << "Error CST";

        sleep(1);
        utils::TimeZone::TimeZone newyork("/usr/share/zoneinfo/America/New_York");
        logx::Logger::setTimeZone(newyork);
        LOG_TRACE << "trace NYT";
        LOG_DEBUG << "debug NYT";
        LOG_INFO << "Hello NYT";
        LOG_WARN << "World NYT";
        LOG_ERROR << "Error NYT";
        g_file = NULL;
    }
}

void func() { LOG_INFO << "logInThread"; }

void test_logger_MultiThread() {
    std::thread t[5];

    for (int i = 0; i < 5; i++) {
        t[i] = std::thread(func);
    }

    for (auto &x : t) {
        x.join();
    }
}

int main() {
    // test_logx_logger();
    // test_logger_TimeZone();
    test_logger_MultiThread();

    return 0;
}