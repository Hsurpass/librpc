#include "../include/RPCEngine.h"
#include "rpc_echo_server.h"
#include <boost/asio/io_context.hpp>
#include <google/protobuf/message.h>
#include <iostream>

using namespace std;
using namespace std::placeholders;
using namespace xrpc;
using namespace logx;

class EchoServer : public EchoService::rpc_echo_server {
public:
    EchoServer() {}

    EchoServer(RPCServerPtr server) : rpc_echo_server(server) {}

    void echo(const echo::EchoRequest &request, echo::EchoResponse &response) override {
        LOG_INFO << request.DebugString();
        response.set_message("world");

        return;
    }

private:
};

int main() {
    logx::Logger::setLogLevel(Logger::DEBUG);

    boost::asio::io_context io;

    // RPCServerPtr rpcserver(new RPCServer(io));
    RPCServerPtr rpcserver = xrpc::RPCEngine::createRPCServer(io);

    EchoServer echoserver(rpcserver);
    rpcserver->start();

    io.run();

    return 0;
}