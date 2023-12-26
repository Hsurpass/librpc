#pragma once

#include "utils/noncopyable.h"
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <string>

// -lboost_system -lboost_filesystem
namespace xrpc {

class RpcEngineConfig : public utils::noncopyable {
public:
    static void createInstanceWithFilePath(std::string path) {
        static RpcEngineConfig instance(path);
        m_instance = &instance;
    }

    static RpcEngineConfig *getInstance() { return m_instance; }
    std::string logLevel() { return m_logLevel; }

private:
    RpcEngineConfig(std::string path);
    void parse(boost::property_tree::ptree *inicfg);

    static RpcEngineConfig *m_instance;
    std::string m_logLevel;
};

} // namespace xrpc