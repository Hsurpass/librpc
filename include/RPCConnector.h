#pragma once

#include "RPCCommon.h"
#include "RPCConnection.h"
#include "net/Connector.h"
#include "net/netCommon.h"
#include <boost/asio/io_context.hpp>
#include <memory>

namespace xrpc {
using namespace net;
using namespace logx;

class RPCConnector : public Connector {
public:
    RPCConnector(boost::asio::io_context &io, std::string serverIP, unsigned short serverPort);
    virtual ~RPCConnector();

    TcpConnectionPtr createConnection() override;

    void set_notifyFunc(NotifyFunc notifyFunc) { m_notifyFunc = notifyFunc; }
    RPCConnectorPtr self() { return std::dynamic_pointer_cast<RPCConnector>(shared_from_this()); }

private:
    NotifyFunc m_notifyFunc;
};

} // namespace xrpc