#pragma once

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ssl.hpp>
#include <google/protobuf/message.h>
#include <memory>

namespace net {

typedef std::shared_ptr<::google::protobuf::Message> MessagePtr;

typedef std::shared_ptr<boost::asio::io_context::strand> StrandPtr;
typedef std::shared_ptr<boost::asio::ssl::context> SSLContextPtr;

class TcpSocket;
typedef std::shared_ptr<TcpSocket> TcpSocketPtr;

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class RequestProcessor;
typedef std::shared_ptr<RequestProcessor> RequestProcessorPtr;
typedef std::weak_ptr<RequestProcessor> RequestProcessorWeakPtr;

class ConnectionManager;
typedef std::shared_ptr<ConnectionManager> ConnectionManagerPtr;
typedef std::weak_ptr<ConnectionManager> ConnectionManagerWeakPtr;

class Acceptor;
typedef std::shared_ptr<Acceptor> AcceptorPtr;

class TcpServer;
typedef std::shared_ptr<TcpServer> TcpServerPtr;
typedef std::weak_ptr<TcpServer> TcpServerWeakPtr;

class Connector;
typedef std::shared_ptr<Connector> ConnectorPtr;

class TcpClient;
typedef std::shared_ptr<TcpClient> TcpClientPtr;
typedef std::weak_ptr<TcpClient> TcpClientWeakPtr;

typedef std::function<void(const boost::system::error_code &error)> CONNECT_CALLBACK;
typedef std::function<void(const boost::system::error_code &error, size_t)> RWCALLBACK;

} // namespace net