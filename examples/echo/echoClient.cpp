// #include "RPCClient.h"
// #include "RPCCommon.h"

#include "echo.pb.h"
#include "rpc_EchoService_client.h"
#include <boost/asio/io_context.hpp>
#include <iostream>

using namespace std;
using namespace std::placeholders;
using namespace xrpc;
using namespace logx;

void on_echo(const echo::EchoResponse &response) {
    //
    LOG_INFO << "response: " << response.message();
}

void on_connect(const XError &error, std::shared_ptr<EchoService::rpc_EchoService_client> client) {
    LOG_INFO << error.to_string();

    echo::EchoRequest request;
    request.set_message("hello");
    client->Echo(request, std::bind(&on_echo, std::placeholders::_1));
}

void run_async_client() {

    boost::asio::io_context io;

    RPCClientrPtr rpcclient(new RPCClient(io));
    std::shared_ptr<EchoService::rpc_EchoService_client> client(new EchoService::rpc_EchoService_client(rpcclient));

    uint64_t id = client->connect(std::bind(&on_connect, _1, client));
    assert(id == CONNECT_ID);

    io.run();
}

int main() {
    run_async_client();

    return 0;
}
