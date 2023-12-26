#pragma once

#include "RPCCommon.h"
#include "net/RequestProcessor.h"
#include "net/TcpConnection.h"
#include "net/netCommon.h"
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <cstdint>
#include <functional>
#include <google/protobuf/message.h>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>

namespace xrpc {

using namespace net;

class RPCRequestProcessor : public RequestProcessor {
public:
    RPCRequestProcessor();
    virtual ~RPCRequestProcessor();

    void setFuncTable(const StubFuncTable &funcTable);
    void registerFunc(const std::string &name, const StubFunc &func);
    virtual void onRequest(const std::string &func, const std::string &param, uint64_t id,
                           TcpConnectionPtr connection) override;

private:
    // std::shared_mutex m_rwMutex;
    boost::shared_mutex m_rwMutex;
    StubFuncTable m_funcTable;
};

} // namespace xrpc
