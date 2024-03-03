#pragma once

#include "netCommon.h"
#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include <string>

namespace net {

// typedef std::function<void(const boost::system::error_code &error)> CONNECT_CALLBACK;
// typedef std::function<void(const boost::system::error_code &error, size_t)> RWCALLBACK;

class TcpSocket : public std::enable_shared_from_this<TcpSocket> {
public:
    static TcpSocketPtr makeTcpSocket(StrandPtr strand);
    static TcpSocketPtr makeTcpsslSocket(StrandPtr strand, SSLContextPtr sslcontext);

    virtual ~TcpSocket() {}

    virtual bool connect(std::string serverIp, int port, boost::system::error_code &error) = 0;
    virtual void async_connect(std::string serverIp, int port, const CONNECT_CALLBACK &callback) = 0;

    virtual void close(boost::system::error_code &error) = 0;
    virtual void cancel(boost::system::error_code &error) = 0;
    virtual boost::system::error_code shutdown(const boost::asio::socket_base::shutdown_type what,
                                               boost::system::error_code &ec) = 0;

    virtual void async_read_some(void *p, size_t len, const RWCALLBACK &callback) = 0;
    virtual void async_write_some(void *p, size_t len, const RWCALLBACK &callback) = 0;

    virtual size_t read_some(void *p, size_t len, boost::system::error_code &error) = 0;
    virtual void write(void *p, size_t len) = 0;

    virtual boost::asio::ip::tcp::endpoint local_endpoint() = 0;
    virtual boost::asio::ip::tcp::endpoint remote_endpoint() = 0;
    virtual boost::asio::ip::tcp::socket &getSocket() = 0;
    virtual std::shared_ptr<tsslSocket> getSSL() = 0;
};

} // namespace net