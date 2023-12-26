#pragma once

#include <exception>
#include <string>

namespace utils {

class Exception : public std::exception {
public:
    Exception(std::string what);
    ~Exception() noexcept override = default;

    // default copy-ctor and operator= are okay.

    const char *what() const noexcept override { return message_.c_str(); }

    const char *stackTrace() const noexcept { return stack_.c_str(); }

private:
    std::string message_; // 异常信息
    std::string stack_;   // 堆栈信息
};
} // namespace utils