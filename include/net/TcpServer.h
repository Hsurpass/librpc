#pragma once

#include "Acceptor.h"
#include "TcpConnection.h"
#include "netCommon.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>
#include <memory>

namespace net {

// class TcpServer;
// typedef std::shared_ptr<TcpServer> TcpServerPtr;

class TcpServer : public ConnectionManager, public std::enable_shared_from_this<TcpServer> {
public:
    TcpServer(boost::asio::io_context &iocontext, const std::string &ip = "127.0.0.1", unsigned short port = 9999,
              bool reuseAddr = true, bool keepalive = true);
    TcpServer(boost::asio::io_context &iocontext, AcceptorPtr acceptor);
    virtual ~TcpServer();

    virtual int32_t start(bool async = true) override;
    virtual int32_t stop() override;

    // void set_serverManager(TcpServerPtr manager);
    // virtual void sendDataToAllClients(ByteArray &data, int32_t len, bool async = true) override;

protected:
    AcceptorPtr m_acceptor;

private:
    // void onDataReceived(const ByteArray &data, int32_t len, TcpConnectionPtr connection) override;

    boost::asio::io_context &m_iocontext;

    // StrandPtr m_serStrand;//todo

    bool m_stopped;
};

} // namespace net