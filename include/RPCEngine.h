#pragma once

// #include "RPCAcceptor.h"
#include "RPCClient.h"
#include "RPCCommon.h"
#include "RPCServer.h"
#include <boost/asio/io_context.hpp>
#include <boost/thread.hpp>
#include <boost/thread/detail/thread_group.hpp>

namespace xrpc {

class RPCEngine {
public:
    ~RPCEngine();
    static RPCEngine *instance();

    boost::asio::io_context &getWorkIO() { return m_workio; }

    RPCClientrPtr createClient(boost::asio::io_context &io, std::string ip = "127.0.0.1", unsigned short port = 9999);
    RPCClientrPtr createClient(std::string ip = "127.0.0.1", unsigned short port = 9999);
    static RPCServerPtr createRPCServer(boost::asio::io_context &io, std::string ip = "127.0.0.1",
                                        unsigned short port = 9999, bool reuseAddr = true, bool keepalive = true);
    RPCServerPtr createRPCServer(std::string ip = "127.0.0.1", unsigned short port = 9999, bool reuseAddr = true,
                                 bool keepalive = true);

private:
    RPCEngine();
    RPCEngine(const char *filePath);
    bool init(const char *filePath);
    void joinAll();

    boost::asio::io_context m_netio;
    boost::asio::io_context::work m_netioWork;
    boost::asio::io_context m_workio;
    boost::asio::io_context::work m_workioWork;
    boost::thread_group m_threadGroup;
};

} // namespace xrpc