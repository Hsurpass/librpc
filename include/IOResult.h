#pragma once

#include "RPCCommon.h"
#include "Result.h"
#include "net/netCommon.h"
#include <condition_variable>
#include <mutex>
#include <string>

namespace xrpc {
using namespace net;

class IOResult : public Result {
public:
    IOResult(bool isAsync, const ResultCallback &cb = ResultCallback());
    virtual ~IOResult() {}

    virtual std::string takeResponse(XError &error = defaultXError) override;
    virtual void giveResponse(const std::string &response, const XError &error = defaultXError) override;
    virtual void waitFinish() override;
    virtual void notify(const std::string &response, const XError &error) override;
    // virtual bool isAnswered() = 0;

private:
    bool m_isAsync;

    std::string m_response;
    XError m_error;

    std::mutex m_mutex;
    std::condition_variable m_cond;

    ResultCallback m_callback; //回调函数
};

} // namespace xrpc