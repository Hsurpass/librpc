#pragma once

#include "../include/RPCClient.h"
#include "../include/log/Logger.h"
#include "../include/rpc.pb.h"
#include "echorpc.pb.h"
#include <cstdint>
#include <functional>
#include <memory>

namespace EchoService {
using namespace std::placeholders;
using namespace xrpc;

class rpc_echo_client {
public:
    rpc_echo_client(RPCClientrPtr client);

    void connect(XError &error = defaultXError);
    typedef std::function<void(const XError &error)> connectCallBack;
    typedef std::shared_ptr<connectCallBack> connectCallBackPtr;
    uint64_t connect(const connectCallBack &callback);

    void disConnect(XError &error = defaultXError);
    typedef std::function<void(const XError &error)> disConnectCallBack;
    typedef std::shared_ptr<disConnectCallBack> disConnectCallBackPtr;
    uint64_t disConnect(const disConnectCallBack &callback);

    void subcribe(const SubScribeRequest &request_, SubScribeResponse &response);
    typedef std::function<void(const SubScribeResponse &)> subscribeCallBack;
    typedef std::shared_ptr<subscribeCallBack> subscribeCallBackPtr;
    uint64_t subscribe(const SubScribeRequest &request_, const subscribeCallBack &callback);

    void echo(const echo::EchoRequest &request_, echo::EchoResponse &response);
    typedef std::function<void(const echo::EchoResponse &)> echoCallBack;
    typedef std::shared_ptr<echoCallBack> echoCallBackPtr;
    uint64_t echo(const echo::EchoRequest &request_, const echoCallBack &callback);

private:
    RPCClientrPtr m_rpcClient;

    std::string request(const std::string &func, MessagePtr request, XError &error = defaultXError);
    uint64_t request(const std::string &func, MessagePtr request, const ResultCallback &cb);

    void on_connect(const std::string &response, const XError &error, connectCallBackPtr cb);
    void on_disconnect(const std::string &response, const XError &error, disConnectCallBackPtr cb);
    void on_subscribe(const std::string &response, const XError &error, subscribeCallBackPtr cb);
    void on_echo(const std::string &response, const XError &error, echoCallBackPtr cb);
};

} // namespace EchoService