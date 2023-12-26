#include "../../include/net/TcpServer.h"
// #include "../../include/net/NetPackage.h"
// #include "../../include/net/netCommon.h"
#include "../../include/log/Logger.h"

#include <iostream>
#include <memory>

using namespace std;
using namespace net;
using namespace logx;

class EchoServer : public net::TcpServer {
public:
    EchoServer(boost::asio::io_context &iocontext, std::string ip = "127.0.0.1", unsigned short port = 9999)
        : TcpServer(iocontext, ip, port) {}

private:
    void onPackageReceived(const NetPackageHeader &header, const char *body, const size_t &bodyLen,
                           TcpConnectionPtr connection) override {

        LOG_INFO << std::string(body, bodyLen);
        ConnectionManager::send(connection, body, bodyLen);
    }
};

int main() {
    logx::Logger::setLogLevel(Logger::DEBUG);

    boost::asio::io_context iocontext;

    std::shared_ptr<EchoServer> echo_server(new EchoServer(iocontext));
    echo_server->start();

    iocontext.run();

    return 0;
}
