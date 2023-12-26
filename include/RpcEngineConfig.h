#pragma once

// #include "utils/noncopyable.h"
#include <boost/core/noncopyable.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <string>

// -lboost_system -lboost_filesystem
namespace xrpc {

class RpcEngineConfig : public boost::noncopyable {
public:
    static void createInstanceWithFilePath(std::string path) {
        static RpcEngineConfig instance(path);
        m_instance = &instance;
    }

    static RpcEngineConfig *getInstance() { return m_instance; }
    std::string logLevel() { return m_logLevel; }
    int netThreadNum() { return m_netThreadNum; }
    int workThreadNum() { return m_workThreadNum; }
    std::string clientIP() { return m_clientIP; }
    unsigned short clientPort() { return m_clientPort; }
    std::string serverIP() { return m_serverIP; }
    unsigned short serverPort() { return m_serverPort; }

private:
    RpcEngineConfig(std::string path);
    void parse(boost::property_tree::ptree *inicfg);

    static RpcEngineConfig *m_instance;
    std::string m_logLevel;
    int m_netThreadNum;
    int m_workThreadNum;
    std::string m_clientIP;
    unsigned short m_clientPort;
    std::string m_serverIP;
    unsigned short m_serverPort;
};

} // namespace xrpc