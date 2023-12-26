#include "../../include/utils/Timestamp.h"
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace utils;

void passByConstReference(const Timestamp &x) { printf("%s\n", x.toString().c_str()); }

void passByValue(Timestamp x) { printf("%s\n", x.toString().c_str()); }

void test_tostring() {

    Timestamp now(Timestamp::now());
    printf("%s\n", now.toString().c_str());
    printf("%s\n", now.toFormattedString().c_str());

    passByValue(now);
    passByConstReference(now);
}

void test_time() {
    time_t now = time(NULL);
    cout << now << endl;
    Timestamp start = Timestamp::now();
    cout << start.toString() << endl;

    sleep(3);
    double diff = utils::timeDifference(Timestamp::now(), start);
    cout << diff << endl;
}

int main() {
    // test_tostring();
    test_time();

    return 0;
}