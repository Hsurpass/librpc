#include "../../include/net/TcpServer.h"
#include <boost/asio/io_context.hpp>
#include <iostream>

using namespace std;
using namespace net;

int main() {
    boost::asio::io_context io_context;

    TcpServerPtr server(new TcpServer(io_context));
    server->start();

    io_context.run();

    return 0;
}