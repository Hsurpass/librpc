#pragma once

#include "RPCCommon.h"
#include "net/netCommon.h"
#include <string>

namespace xrpc {
using namespace net;

class Result {
public:
    virtual ~Result() {}
    virtual std::string takeResponse(XError &error = defaultXError) = 0;
    virtual void giveResponse(const std::string &response, const XError &error = defaultXError) = 0;
    virtual void waitFinish() = 0;
    virtual void notify(const std::string &response, const XError &error) = 0;
};

} // namespace xrpc
