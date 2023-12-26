#include "../../include/utils/TimeZone.h"
#include <cstring>
#include <iostream>

using namespace std;
using namespace utils::TimeZone;

struct tm getTm(int year, int month, int day, int hour, int minute, int seconds) {
    struct tm gmt;
    memset(&gmt, 0, sizeof gmt);
    gmt.tm_year = year - 1900;
    gmt.tm_mon = month - 1;
    gmt.tm_mday = day;
    gmt.tm_hour = hour;
    gmt.tm_min = minute;
    gmt.tm_sec = seconds;
    return gmt;
}

struct tm getTm(const char *str) {
    struct tm gmt;
    memset(&gmt, 0, sizeof gmt);
    strptime(str, "%F %T", &gmt);
    return gmt;
}

time_t getGmt(int year, int month, int day, int hour, int minute, int seconds) {
    struct tm gmt = getTm(year, month, day, hour, minute, seconds);
    return timegm(&gmt);
}

time_t getGmt(const char *str) {
    struct tm gmt = getTm(str);
    return timegm(&gmt);
}

struct TestCase {
    const char *gmt;
    const char *local;
    bool isdst;
};

void test(const TimeZone &tz, TestCase tc) {
    time_t gmt = getGmt(tc.gmt); // gmt字符串转化为时间戳

    {
        struct tm local = tz.toLocalTime(gmt); //gmt时间戳转化为本地时间
        char buf[256];
        strftime(buf, sizeof buf, "%F %T%z(%Z)", &local); // 本地时间 tm转化为字符串

        if (strcmp(buf, tc.local) != 0 || tc.isdst != local.tm_isdst) // 转化的本地时间和tc.local相比
        {
            printf("WRONG: ");
        }
        printf("%s -> %s\n", tc.gmt, buf);
    }

    {
        struct tm local = getTm(tc.local); // tc.local本地字符串通过strptime转化为tm
        local.tm_isdst = tc.isdst;
        time_t result = tz.fromLocalTime(local); // tm转换成gmt时间戳
        if (result != gmt) {
            struct tm local2 = tz.toLocalTime(result);
            char buf[256];
            strftime(buf, sizeof buf, "%F %T%z(%Z)", &local2);

            printf("WRONG fromLocalTime: %ld %ld %s\n", static_cast<long>(gmt), static_cast<long>(result), buf);
        }
    }
}

void testHongKong() {
    TimeZone tz("/usr/share/zoneinfo/Asia/Hong_Kong");
    TestCase cases[] = {

        {"2011-04-03 00:00:00", "2011-04-03 08:00:00+0800(HKT)", false},

    };

    for (const auto &c : cases) {
        test(tz, c);
    }
}

int main() {
    testHongKong();

    return 0;
}
