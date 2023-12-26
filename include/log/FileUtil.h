#pragma once

#include "../utils/noncopyable.h"
#include <string>

namespace logx {
namespace FileUtil {

/*
    @brief: 写入数据
*/
// not thread safe 非线程安全的，因为没加锁
// 这个类隐藏着减少磁盘IO的秘密
class AppendFile : utils::noncopyable {
public:
    explicit AppendFile(std::string filename);
    ~AppendFile();

    // 添加字符串到文件
    void append(const char *logline, size_t len);
    void flush();
    off_t writtenBytes() const { return writtenBytes_; }

private:
    size_t write(const char *logline, size_t len);

    FILE *fp_;               // 打开的文件指针
    char buffer_[64 * 1024]; // 文件缓冲区/用户态缓冲区 减少磁盘IO的次数
    off_t writtenBytes_;     // 已写入字节数
};

} // namespace FileUtil

} // namespace logx