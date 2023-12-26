#pragma once

#include <condition_variable>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace utils {

class ThreadPool {
public:
    typedef std::function<void()> Task;

    explicit ThreadPool(const std::string &nameArg = std::string("ThreadPool"));
    ~ThreadPool();

    // Must be called before start().
    void setMaxQueueSize(int maxSize) { m_maxQueueSize = maxSize; }
    void setThreadInitCallback(const Task &cb) { m_threadInitCallback = cb; }

    void start(int numThreads);
    void stop();

    const std::string &name() const { return m_name; }

    size_t queueSize() const;
    void addTask(const Task& task);

private:
    bool isFull();
    Task getTask();
    void runTask();

    std::string m_name;
    Task m_threadInitCallback;

    mutable std::mutex m_mutex;
    std::condition_variable m_queueEmpty;
    std::condition_variable m_queueFull;

    std::vector<std::unique_ptr<std::thread>> m_threads; // 消费者
    std::deque<Task> m_queue;
    size_t m_maxQueueSize;
    bool m_running;
};

} // namespace utils