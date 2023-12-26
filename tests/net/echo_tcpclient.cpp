#include "../../include/log/Logger.h"
#include "../../include/net/TcpClient.h"
#include <boost/asio/io_context.hpp>
#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

using namespace std;
using namespace net;
using namespace logx;

class echo_tcpclient : public TcpClient {
public:
    echo_tcpclient(boost::asio::io_context &iocontext, std::string serverIp = "127.0.0.1",
                   unsigned short serverPort = 9999)
        : TcpClient(iocontext, serverIp, serverPort) {
        start();
    }

private:
};

int main() {
    Logger::setLogLevel(Logger::DEBUG);
    boost::asio::io_context iocontext;

    echo_tcpclient echo_client(iocontext);
    // echo_client.start();

    // std::this_thread::sleep_for(std::chrono::seconds(2));
    const char *p = "hello!!!";
    int len = strlen(p);

    echo_client.send(p, len);

    std::thread t([&echo_client]() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        const char *p1 = "world";
        echo_client.send(p1, strlen(p1));
    });

    iocontext.run();

    // std::thread t[2];
    // for (int i = 0; i < 2; i++) {
    //     t[i] = std::thread([&iocontext]() { iocontext.run(); });
    // }

    // for (auto &x : t) {
    //     x.join();
    // }

    return 0;
}
