#include "../../include/net/TcpClient.h"
#include <boost/asio/io_context.hpp>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

int main() {
    boost::asio::io_context iocontext;

    net::TcpClient client(iocontext);
    client.start(false);

    client.send("hello world", 11);

    iocontext.run();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}
