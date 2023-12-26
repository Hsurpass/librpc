#pragma once

#include "ConnectionManager.h"
#include "Connector.h"
#include "netCommon.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <memory>
#include <mutex>
#include <string>

namespace net {

class TcpClient : public ConnectionManager, public std::enable_shared_from_this<TcpClient> {
public:
    TcpClient(boost::asio::io_context &iocontext, std::string serverIp = "127.0.0.1", unsigned short serverPort = 9999);
    virtual ~TcpClient();

    int32_t start(bool async = true) override;
    int32_t stop() override;
    bool isConnected();

    TcpConnectionPtr getConnection();

    bool send(ByteArray &data, int32_t len, bool async = true);
    bool send(const char *data, int32_t len, bool async = true);
    size_t receiveSync(char *buf, int32_t len);

protected:
    boost::asio::io_context &m_iocontext;

    ConnectorPtr m_connector;
    // std::mutex m_mutex;
};

} // namespace net