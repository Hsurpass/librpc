#pragma once

#include "../utils/noncopyable.h"
#include "FixedBuffer.h"
#include <assert.h>
#include <string>

namespace logx {

class LogStream : public ::utils::noncopyable {
public:
    typedef SmallBuffer Buffer;
    // typedef LargeBuffer Buffer;

    LogStream &operator<<(bool v);

    LogStream &operator<<(short v);
    LogStream &operator<<(unsigned short v);
    LogStream &operator<<(int v);
    LogStream &operator<<(unsigned int v);
    LogStream &operator<<(long v);
    LogStream &operator<<(unsigned long v);
    LogStream &operator<<(long long v);
    LogStream &operator<<(unsigned long long v);
    LogStream &operator<<(const void *p);

    LogStream &operator<<(float v);
    LogStream &operator<<(double);
    // LogStream& operator<<(long double);

    LogStream &operator<<(char v);

    // LogStream& operator<<(signed char);
    // LogStream& operator<<(unsigned char);

    LogStream &operator<<(const char *str);
    LogStream &operator<<(const unsigned char *str);
    LogStream &operator<<(const std::string &v);

    // LogStream &operator<<(const StringPiece &v) {
    //     m_buffer.append(v.data(), v.size());
    //     return *this;
    // }

    // LogStream &operator<<(const SmallBuffer &v) {
    //     *this << v.toStringPiece();
    //     return *this;
    // }
    void append(const char *data, int len) { m_buffer.append(data, len); }
    const Buffer &buffer() const { return m_buffer; }
    void resetBuffer() { m_buffer.reset(); }

private:
    template <typename T>
    void formatInteger(T v);

    Buffer m_buffer;
    static const int kMaxNumericLength = 48;
};

class Fmt // : noncopyable
{
public:
    template <typename T>
    Fmt(const char *fmt, T val);

    const char *data() const { return buf_; }
    int length() const { return length_; }

private:
    char buf_[32];
    int length_;
};

inline LogStream &operator<<(LogStream &s, const Fmt &fmt) {
    s.append(fmt.data(), fmt.length());
    return s;
}

// helper class for known string length at compile time
class T {
public:
    T(const char *str, unsigned len) : str_(str), len_(len) { assert(strlen(str) == len_); }

    const char *str_;
    const unsigned len_;
};

inline LogStream &operator<<(LogStream &s, T v) {
    s.append(v.str_, v.len_);
    return s;
}

} // namespace logx