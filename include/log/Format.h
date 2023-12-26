#pragma once

#include "stdint.h"
#include <algorithm>

namespace logx {

const char digits[] = "9876543210123456789";
const char *zero = digits + 9;
static_assert(sizeof(digits) == 20, "wrong number of digits");

const char digitsHex[] = "0123456789ABCDEF";
static_assert(sizeof digitsHex == 17, "wrong number of digitsHex");

// Efficient Integer to String Conversions, by Matthew Wilson.
template <typename T>
std::size_t convert(char buf[], T value) {
    T i = value;
    char *p = buf;

    do {
        int lsd = static_cast<int>(i % 10); // 最后一个数字
        i /= 10;
        *p++ = zero[lsd];
    } while (i != 0);

    if (value < 0) {
        *p++ = '-';
    }
    *p = '\0';
    std::reverse(buf, p);

    return p - buf;
}

size_t convertHex(char buf[], uintptr_t value) {
    uintptr_t i = value;
    char *p = buf;

    do {
        int lsd = static_cast<int>(i % 16); // 16进制
        i /= 16;
        *p++ = digitsHex[lsd];
    } while (i != 0);

    *p = '\0';
    std::reverse(buf, p);

    return p - buf;
}

} // namespace logx