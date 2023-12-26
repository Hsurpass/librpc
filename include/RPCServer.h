#pragma once

#include "RPCAcceptor.h"
#include "RPCCommon.h"
#include "RPCRequestProcessor.h"
#include "net/TcpServer.h"
#include "net/netCommon.h"
#include <boost/asio/io_context.hpp>
#include <cstdint>
#include <google/protobuf/message.h>
#include <map>

namespace xrpc {

using namespace net;
using namespace logx;

class RPCServer : public TcpServer, public RPCRequestProcessor {
public:
    RPCServer(boost::asio::io_context &io, const std::string &ip = "127.0.0.1", unsigned short port = 9999,
              const StubFuncTable &table = StubFuncTable(), bool reuseAddr = true, bool keepalive = true);

    RPCServer(boost::asio::io_context &io, RPCAcceptorPtr acceptor);
    virtual ~RPCServer() {}

    int32_t start(bool async = true) override;
    int32_t stop() override;

private:
    RPCServerPtr self();
};

} // namespace xrpc