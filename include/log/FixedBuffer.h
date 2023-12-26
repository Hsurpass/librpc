#pragma once

#include "../utils/noncopyable.h"
#include <cstddef>
#include <string.h>
#include <string>

namespace logx {

const int kSmallBuffer = 4000;        //4k
const int kLargeBuffer = 4000 * 1000; //4M

template <int SIZE>
class FixedBuffer : public utils::noncopyable {
public:
    FixedBuffer() : m_cur(m_data) {}
    ~FixedBuffer() {}

    const char *data() const { return m_data; }
    int length() const { return static_cast<int>(m_cur - m_data); }

    char *current() const { return m_cur; }
    const char *end() const { return m_data + sizeof(m_data); }
    int avail() const { return static_cast<int>(end() - m_cur); }

    void append(const char *buf, std::size_t len) {
        if (avail() > len) {
            memcpy(m_cur, buf, len);
            m_cur += len;
        }
    }
    void add(size_t len) { m_cur += len; }

    void reset() { m_cur = m_data; }
    void bzero() { memset(m_data, 0, sizeof(m_data)); }

    const char *debugString() {
        *m_cur = '\0';
        return m_data;
    }
    // for used by unit test
    std::string toString() const { return std::string(m_data, length()); }

private:
    char m_data[SIZE];
    char *m_cur;
};
/*
    data
      ————————
      |a|b| | |
      ————————
           curr
*/

typedef FixedBuffer<kSmallBuffer> SmallBuffer;
typedef FixedBuffer<kLargeBuffer> LargeBuffer;

} // namespace logx