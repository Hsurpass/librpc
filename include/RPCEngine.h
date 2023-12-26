#pragma once

#include "RPCAcceptor.h"
#include "RPCCommon.h"
#include "RPCServer.h"

namespace xrpc {

class RPCEngine {
public:
    static RPCServerPtr createRPCServer(boost::asio::io_context &io, std::string ip = "127.0.0.1",
                                        unsigned short port = 9999, bool reuseAddr = true, bool keepalive = true);
};
} // namespace xrpc