#pragma once

#include "netCommon.h"
#include <string>

namespace net {

class RequestProcessor {
public:
    RequestProcessor();
    virtual ~RequestProcessor();

    virtual void onRequest(const std::string &func, const std::string &param, uint64_t id,
                           TcpConnectionPtr connection) {}

private:
};

} // namespace net