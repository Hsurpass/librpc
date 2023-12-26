#include "rpc_echo_server.h"

namespace EchoService {

rpc_echo_server::rpc_echo_server() {}
rpc_echo_server::rpc_echo_server(RPCServerPtr server) : m_server(server) { registFunc(); }

void rpc_echo_server::registFunc() {
    if (m_server) {
        m_server->setFuncTable(genFuncTable());
    }
}

StubFuncTable rpc_echo_server::genFuncTable() {
    StubFuncTable table;
    table.emplace("subscribe", std::bind(&rpc_echo_server::subscribe_, this, _1, _2, _3));
    table.emplace("echo", std::bind(&rpc_echo_server::echo_, this, _1, _2, _3));

    return table;
}

MessagePtr rpc_echo_server::subscribe_(const std::string &param, uint64_t id, TcpConnectionPtr connection) {
    SubScribeRequest request;
    request.ParseFromString(param);

    SubScribeResponse response;
    subscribe(request, response);
    LOG_DEBUG << "response: " << response.subscriberesponse();

    ByteArray bytes;
    makeRPCResponse(bytes, &response, id);
    if (bytes.size() > 0) {
        connection->send(bytes, bytes.size());
    } else {
        LOG_ERROR << "make response package failed";
    }

    return MessagePtr();
}

void rpc_echo_server::subscribe(const SubScribeRequest &request_, SubScribeResponse &response) {
    response.set_subscriberesponse("success");
}

MessagePtr rpc_echo_server::echo_(const std::string &param, uint64_t id, TcpConnectionPtr connection) {
    echo::EchoRequest request;
    request.ParseFromString(param);

    echo::EchoResponse response;
    echo(request, response);
    LOG_DEBUG << "response: " << response.message();

    ByteArray bytes;
    makeRPCResponse(bytes, &response, id);
    if (bytes.size() > 0) {
        connection->send(bytes, bytes.size());
    } else {
        LOG_ERROR << "make response package failed";
    }

    return MessagePtr();
}

void rpc_echo_server::echo(const echo::EchoRequest &request, echo::EchoResponse &response) {
    LOG_INFO << request.DebugString();
    response.set_message("world");
}

} // namespace EchoService
