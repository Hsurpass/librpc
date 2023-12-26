#pragma once

#include "ConnectionManager.h"
#include "TcpClient.h"
#include "netCommon.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <condition_variable>
#include <functional>
#include <memory>
#include <vector>

namespace net {

class Connector : public ConnectionManager, public std::enable_shared_from_this<Connector> {
    typedef std::function<bool()> Task;

public:
    Connector(boost::asio::io_context &io, std::string serverIP, unsigned short serverPort);
    virtual ~Connector();

    int32_t start(bool async = true) override;
    int32_t stop() override;
    bool isConnected();
    TcpConnectionPtr getConnection();

    void set_clientManager(TcpClientPtr manager);
    // void set_requestProcessor(RequestProcessorPtr processor) { m_requestProcessor = processor; }

    bool send(const ByteArray &data, int32_t len, bool async = true);
    bool send(const char *data, int32_t len, bool async = true);
    size_t receiveSync(char *buf, int32_t len);

protected:
    TcpConnectionPtr createConnection() override;

    void connectSync();
    void connectAsync();
    void onConnect(TcpConnectionPtr connection, const boost::system::error_code &error);
    bool isConnected_();

    void onConnectionError(const boost::system::error_code &err, TcpConnectionPtr connection) override;
    void reConnect(int seconds);
    void onReconnectTimer(const boost::system::error_code &error);

    boost::asio::io_context &m_iocontext;
    StrandPtr m_connectorStrand;

    bool m_isConnected;
    std::string m_serverIP;
    unsigned short m_serverPort;
    TcpConnectionPtr m_connection;

    TcpClientWeakPtr m_clientManager;
    // RequestProcessorWeakPtr m_requestProcessor;
    std::vector<Task> m_taskPool;

    boost::asio::steady_timer m_reconnectTimer;
    std::mutex m_mutex;
    std::condition_variable m_cond;
};

} // namespace net