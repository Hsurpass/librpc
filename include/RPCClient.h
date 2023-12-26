#pragma once

#include "RPCCommon.h"
#include "RPCConnection.h"
#include "net/TcpClient.h"
#include "net/netCommon.h"
#include <boost/asio/io_context.hpp>
#include <memory>
#include <string>

namespace xrpc {
using namespace net;
using namespace logx;

class RPCClient : public TcpClient {
public:
    RPCClient(boost::asio::io_context &netIO, std::string ip = "127.0.0.1", unsigned short port = 9999);
    RPCClient(StrandPtr strand, std::string ip = "127.0.0.1", unsigned short port = 9999);
    ~RPCClient();

    int32_t start(bool async = true) override;
    int32_t stop() override;

    std::string requestSync(const std::string &func, MessagePtr request, XError &error = defaultXError);
    uint64_t requestAsync(const std::string &func, MessagePtr request, const ResultCallback &cb);

    RPCConnectionPtr getConnection();
    void set_notifyFunc(NotifyFunc notifyFunc);

private:
    RPCClientrPtr self();
    void sendRequest(const std::string &func, MessagePtr request, ResultPtr result, uint64_t &id);

    virtual void onConnected(TcpConnectionPtr connection) override;

    StrandPtr m_strand;
    std::mutex m_mutex;
    ResultPtr m_connectResult;
};

} // namespace xrpc