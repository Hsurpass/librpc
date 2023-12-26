#pragma once

#include "FixedBuffer.h"
#include <assert.h>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace logx {

class AsyncLogger {
public:
    AsyncLogger(const std::string &basename, off_t rollSize, int flushInterval = 3 /*3秒*/);
    ~AsyncLogger();

    void start();
    void stop();

    // 供前端生产者线程调用(日志数据写到缓冲区)
    void append(const char *logline, int len);

private:
    void threadFunc(); // 供后端消费者线程调用，将数据写到日志文件中

    typedef LargeBuffer Buffer; // 固定大小的缓冲区 4M
    typedef std::vector<std::unique_ptr<Buffer>> BufferVector;
    typedef BufferVector::value_type BufferPtr;

    const int flushInterval_; //超过时间，在flushInterval_秒内，缓冲区没写满，仍将缓冲区中的数据写到文件中
    std::atomic<bool> running_;
    const std::string basename_;
    const off_t rollSize_; // 日志文件的滚动大小

    std::thread thread_;
    std::mutex mutex_;
    std::condition_variable cond_;

    BufferPtr currentBuffer_; //当前缓冲区
    BufferPtr nextBuffer_;    //预备缓冲区
    BufferVector buffers_;    //待写入文件的已填满的缓冲区，也可以是没填满的(到时的)
};

} // namespace logx