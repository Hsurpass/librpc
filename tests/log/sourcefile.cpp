// #include "gtest/gtest.h"
#include <iostream>
#include <string.h>
// #include "../../include/log

using namespace std;

class SourceFile {
public:
    template <int N>                 // 非类型模板参数 构造函数可隐式转换
    SourceFile(const char (&arr)[N]) // 匹配字符数组写法 因为是引用 效率更高一点
        : data_(arr), size_(N - 1)   // 10-1
    { // 找到路径中的文件名， 返回第二个参数('/')最后一次出现的位置的指针
        const char *slash = strrchr(data_, '/'); // builtin function
        if (slash) {
            // 0 1 2 3 4 5 6 7 8 9
            // / m n t / t e s t \0
            data_ = slash + 1;
            size_ -= static_cast<int>(data_ - arr); // 9 - (5-0)
        }
    }

    explicit SourceFile(const char *filename) : data_(filename) {
        const char *slash = strrchr(filename, '/');
        if (slash) {
            data_ = slash + 1;
        }
        size_ = static_cast<int>(strlen(data_));
    }

    const char *data_;
    int size_;
};

void test1(SourceFile f) { cout << f.data_ << endl; }

void func(const char *str) { cout << str << endl; }

int main() {
    // cout << __FILE__ << endl;
    // test1(__FILE__);

    // SourceFile f(__FILE__);
    // cout << f.data_ << endl;

    // SourceFile f1 = "a.cpp";
    // cout << f1.data_ << endl;

    int v = 1;
#define xx(val) "'" #val "' Must be non NULL"
    // func("'" #val "' Must be non NULL");
    func(xx(v));

    return 0;
}