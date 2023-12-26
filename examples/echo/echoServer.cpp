#include "RPCCommon.h"
#include "RPCEngine.h"
#include "rpc_EchoService_server.h"
#include <boost/asio/io_context.hpp>

using namespace std;
using namespace std::placeholders;
using namespace xrpc;
using namespace logx;

class EchoServer : public EchoService::rpc_EchoService_server {
public:
    EchoServer() {}
    EchoServer(RPCServerPtr server) : rpc_EchoService_server(server) {}

    void Echo(const echo::EchoRequest &request, echo::EchoResponse &response) override {
        LOG_INFO << request.DebugString();
        response.set_message("world");

        return;
    }
};

int main() {
    boost::asio::io_context io;

    RPCServerPtr rpcserver = xrpc::RPCEngine::createRPCServer(io);
    EchoServer echoserver(rpcserver);
    rpcserver->start();

    io.run();

    return 0;
}