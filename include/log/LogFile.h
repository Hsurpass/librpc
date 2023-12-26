#pragma once

#include "FileUtil.h"
#include <assert.h>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

namespace logx {

namespace FileUtil {
class AppendFile;
}

class LogFile {
public:
    LogFile(const std::string &basename,
            off_t rollSize,          // 一次最大刷新字节数
            bool threadSafe = true,  // 通过对写入操作加锁，来决定是否线程安全
            int flushInterval = 3,   // 隔多少毫秒刷新一次
            int checkEveryN = 1024); // 允许写入的最大条数
    ~LogFile();

    void append(const char *logline, int len);
    void flush();    // 清空缓冲区
    bool rollFile(); // 滚动日志

private:
    void append_unlocked(const char *logline, int len);

    static std::string getLogFileName(const std::string &basename, time_t *now); // 获取日志文件的名称

    bool threadSafe_;
    const std::string basename_; // 日志文件basename
    const off_t rollSize_;       // 日志文件达到rollSize_ 换一个新文件
    const int flushInterval_;    // 日志写入时间间隔
    const int checkEveryN_;

    int count_;

    std::mutex mutex_;
    time_t startOfPeriod_; // 开始记录日志时间(调整至零点)
    time_t lastRoll_;      // 上一次滚动日志文件时间
    time_t lastFlush_;     // 上一次日志写入时间
    std::unique_ptr<FileUtil::AppendFile> file_;

    const static int kRollPerSeconds_ = 60 * 60 * 24; // 一天的秒数
};

} // namespace logx