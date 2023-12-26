#pragma once

#include "NetPackage.h"
#include "TcpConnection.h"
#include "commonType.h"
#include "netCommon.h"
#include <memory>
#include <mutex>
#include <set>

namespace net {

class ConnectionManager {
public:
    ConnectionManager();
    virtual ~ConnectionManager();

    virtual int32_t start(bool async = true) { return 0; }

    virtual int32_t stop() { return 0; }

    virtual void onConnected(TcpConnectionPtr connection) { LOG_DEBUG << "ConnectionManager::onConnected"; }

    virtual void onConnectionError(const boost::system::error_code &err, TcpConnectionPtr connection) {}

    virtual void onDataReceived(const ByteArray &data, int32_t len, TcpConnectionPtr connection);

    virtual void onPackageReceived(const NetPackageHeader &header, const char *body, const size_t &bodyLen,
                                   TcpConnectionPtr connection);

    virtual void onDataSend(int32_t len, TcpConnectionPtr connection) {}

    virtual TcpConnectionPtr createConnection();

    void startConnection(TcpConnectionPtr connection);

    std::set<TcpConnectionPtr> getAllConnections();

    void addConnection(TcpConnectionPtr connection);

    void removeConnection(TcpConnectionPtr connection);

    void removeAllConnections();

    bool send(TcpConnectionPtr connection, const ByteArray &data, int32_t len, bool async = true);
    bool send(TcpConnectionPtr connection, const char *data, int32_t len, bool async = true);
    virtual void sendDataToAllClients(ByteArray &data, int32_t len, bool async = true);

private:
    std::recursive_mutex m_mutex;
    std::set<TcpConnectionPtr> m_connectionPool;
};

} // namespace net