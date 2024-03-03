#pragma once

#include "../../include/log/Logger.h"
#include "ConnectionManager.h"
#include "NetPackageParser.h"
#include "TcpSocket.h"
#include "netCommon.h"
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
// #include <boost/system/detail/error_code.hpp>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>

namespace net {

// class ConnectionManager;

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
    // friend ConnectionManager;
    // typedef std::function<void(const boost::system::error_code &error)> CallBack;
    // typedef std::function<void()> CallBack;

public:
    TcpConnection(StrandPtr strand, TcpSocketPtr socket);
    virtual ~TcpConnection();

    int32_t start();
    void close();
    bool isConnected();

    void connectSync(std::string serverIp, int port, boost::system::error_code &error);
    void connectAsync(std::string serverIp, int port, const CONNECT_CALLBACK &callback);

    bool send(const ByteArray &data, uint32_t len, bool async = true);
    bool send(const char *data, uint32_t len, bool async = true);
    size_t receiveSync(char *buf, size_t len);

    void setNetManager(ConnectionManagerPtr connManager);
    void setRequestProcessor(RequestProcessorPtr processor) { m_requestProcessor = processor; };

    NetPackageParser &getPkgParser() { return m_pkgParser; }

    boost::asio::ip::tcp::socket &getSocket();
    TcpSocketPtr getSocketPtr();

    void setPeerAddress(std::string ip) { m_peerIp = ip; }
    void setPeerPort(unsigned short port) { m_peerPort = port; }

    std::string localAddress() const;
    std::string peerAddress() const;

    void sendKeepalive(const boost::system::error_code &error);
    void timeoutCheck(const boost::system::error_code &error);
    void setKeepAliveInterval(int32_t interval) { m_keepaliveInterval = interval; };
    void setTimeOutInterval(int32_t interval) { m_timeoutInterval = interval; };

protected:
    virtual void onConnected();
    virtual void onConnectionError(const boost::system::error_code &error);
    virtual void onDataReceived(const ByteArray &data, int32_t len);
    virtual void onPackageReceived(const NetPackageHeader &header, const char *body, const size_t &bodyLen);
    virtual void onDataSend(int32_t len);
    virtual void doClose();

private:
    void init();

    void handleConnectionError(const boost::system::error_code &err);

    void doReceive();
    void onReceive(const boost::system::error_code &err, int32_t bytesReceived);

    bool sendSync(const ByteArray &data, uint32_t len);
    bool sendAsync(const ByteArray &data, uint32_t len);
    void doSend();
    void onSend(const boost::system::error_code &err, int32_t bytesSend);
    bool moveWaitToSend();

    void doSendKeepalive(const boost::system::error_code &error);
    void doTimeoutCheck(const boost::system::error_code &error);

protected:
    RequestProcessorWeakPtr m_requestProcessor;

private:
    // StrandPtr m_sendStrand;
    // StrandPtr m_receiveStrand;
    // StrandPtr m_pkgParserStrand;

    bool m_connected;
    StrandPtr m_connectionStrand;
    TcpSocketPtr m_socket;
    std::string m_peerIp;
    unsigned short m_peerPort;

    std::recursive_mutex m_mutex;
    ConnectionManagerWeakPtr m_connectionManager;

    NetPackageParser m_pkgParser;
    ByteArray m_recvBuf;
    int32_t m_recvBufLen;
    // ByteArray m_recvBuf2; //todo
    
    ByteArray m_sendBuf;
    int32_t m_sendBufLen;
    int32_t m_sentLen;
    ByteArray m_waitBuf;
    int32_t m_waitBufLen;
    bool m_isSending;

    utils::Timestamp m_lastSendTime;
    utils::Timestamp m_lastRecvTime;

    utils::Timestamp m_lastKeepaliveTime;
    boost::asio::steady_timer m_sendKATimer;
    int32_t m_keepaliveInterval; // 单位：秒
    boost::asio::steady_timer m_timeoutTimer;
    int32_t m_timeoutInterval; // 单位：秒
};

} // namespace net