#pragma once

#include "NetPackage.h"
#include "commonType.h"
#include <iostream>
#include <vector>

namespace net {

class NetPackageParser {
public:
    typedef std::vector<char> ByteArray;
    NetPackageParser();

    void reset();

    void fillData(const ByteArray &data, size_t len);

    bool nextPackage(NetPackageHeader *header, char **p, size_t *len, bool *isReset = NULL);

    void moveData();

    // void moveIndex();

    ByteArray getRemainData(NetPackageHeader *header, char **p, size_t *len);

private:
    ByteArray m_buffer;
    size_t m_dataLen;   // 缓冲区数据长度
    size_t m_dataIndex; // 上次解析缓冲区的位置
};

} // namespace net