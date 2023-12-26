#pragma once

#include "RequestProcessor.h"
#include "TcpConnection.h"
#include "TcpServer.h"
#include "netCommon.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>
#include <memory>

namespace net {

// class TcpServerPtr;

// class Acceptor;
// typedef std::shared_ptr<Acceptor> AcceptorPtr;

class Acceptor : public ConnectionManager, public std::enable_shared_from_this<Acceptor> {

public:
    Acceptor(boost::asio::io_context &iocontext, const std::string &ip, unsigned short port, bool reuseAddr,
             bool keepalive);
    virtual ~Acceptor();

    virtual int32_t start(bool async = true) override;
    virtual int32_t stop() override;

    void set_serverManager(TcpServerPtr manager);
    void set_requestProcessor(RequestProcessorPtr processor);

protected:
    boost::asio::io_context &m_iocontext;

private:
    void init();
    TcpConnectionPtr createConnection() override;

    void do_accept();
    void on_accept(const boost::system::error_code &error, TcpConnectionPtr connection);

    void onReListenTimer(const boost::system::error_code &error);
    void onReAcceptTimer(const boost::system::error_code &error);

    bool m_stopped;
    std::string m_serverIp;
    unsigned short m_serverPort;

    StrandPtr m_acceptorStrand;
    boost::asio::ip::tcp::acceptor m_acceptor;

    TcpServerWeakPtr m_serverManager;
    RequestProcessorWeakPtr m_requestProcessor;

    // socket option
    bool m_reuseAddress;
    bool m_keepalive;

    boost::asio::steady_timer m_reAcceptorTimer;
    boost::asio::steady_timer m_reListenTimer;
};

} // namespace net