#pragma once

#include "RPCCommon.h"
#include "RPCRequestProcessor.h"
#include "Result.h"
#include "net/TcpConnection.h"
#include "net/netCommon.h"
#include <cstdint>
#include <google/protobuf/message.h>
#include <memory>
#include <mutex>

namespace xrpc {

using namespace net;
using namespace logx;

class RPCConnection : public TcpConnection {
    typedef std::map<uint64_t, ResultPtr> ResultTable;

public:
    RPCConnection(StrandPtr strand, TcpSocketPtr socket);
    virtual ~RPCConnection();

    MessagePtr request(const std::string &func, MessagePtr request, ResultPtr result, uint64_t &id);

    void set_notifyFunc(NotifyFunc notifyFunc) { m_notifyFunc = notifyFunc; }

private:
    uint64_t genId(const std::string &func);
    bool sendRequest(const std::string &func, MessagePtr request, const uint64_t &id);
    bool sendData(const std::string &func, MessagePtr request, const uint64_t &id);
    void makeRPCPackage(ErrorCode errCode, const uint64_t id, const std::string &response);

    virtual void onDataReceived(const ByteArray &data, int32_t len) override;
    virtual void onPackageReceived(const NetPackageHeader &header, const char *body, const size_t &bodyLen) override;

    std::mutex m_mutex;
    StrandPtr m_strand;
    StrandPtr m_dispatchStrand;

    uint64_t m_requestId;
    ResultTable m_resultTable;

    NotifyFunc m_notifyFunc;
};

} // namespace xrpc