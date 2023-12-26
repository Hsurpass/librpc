#pragma once

#include "net/Acceptor.h"
#include "net/netCommon.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>

namespace xrpc {
using namespace net;

class RPCAcceptor : public Acceptor {
public:
    RPCAcceptor(boost::asio::io_context &io, const std::string& ip, unsigned short port, bool reuseAddr = true,
                bool keepalive = true);
    virtual ~RPCAcceptor();

    TcpConnectionPtr createConnection() override;
};

} // namespace xrpc