#pragma once

#include "../include/RPCCommon.h"
#include "../include/RPCServer.h"
#include "../include/log/Logger.h"
#include "../include/rpc.pb.h"
#include "echorpc.pb.h"
#include <functional>

namespace EchoService {
using namespace std::placeholders;
using namespace xrpc;
using namespace logx;

class rpc_echo_server {
public:
    rpc_echo_server();
    rpc_echo_server(RPCServerPtr server);

    void registFunc();
    StubFuncTable genFuncTable();

    virtual void subscribe(const SubScribeRequest &request_, SubScribeResponse &response);
    virtual void echo(const echo::EchoRequest &request, echo::EchoResponse &response);

private:
    RPCServerPtr m_server;

    MessagePtr subscribe_(const std::string &param, uint64_t id, TcpConnectionPtr connection);
    MessagePtr echo_(const std::string &param, uint64_t id, TcpConnectionPtr connection);
};
} // namespace EchoService