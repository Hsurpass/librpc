#pragma once

#include "commonType.h"

namespace net {

const uint32_t NET_PACKAGE_HEADER_LENGTH = 4;                  //网络包头长度
const uint32_t NET_PACKAGE_INVALID_LENGTH = 512 * 1024 * 1024; //最大网络包长度

class NetPackageHeader {
public:
    NetPackageHeader(uint32_t length = 0);
    // NetPackageHeader(uint64_t seq = 0);

    int32_t encode(ByteArray &data, int32_t pos = 0);
    ByteArray encode();

    int32_t decode(const ByteArray &data, int32_t nPos = 0);
    int32_t decode(const char *data, int32_t nPos = 0);

    uint32_t m_length;
    // uint64_t m_seq;

private:
};

class NetPackage {
public:
    NetPackage();

    ByteArray encode();

    int32_t encode(ByteArray &data, int32_t pos = 0);

    int32_t decode(const ByteArray &data, int32_t pkgLength, int32_t pos = 0);

    int32_t decode(const char *data, int32_t pkgLength, int32_t pos = 0);

    NetPackageHeader m_pkgHeader;
    ByteArray m_pkgBody;
};

} // namespace net