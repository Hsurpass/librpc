#include "../include/log/AsyncLogger.h"
#include "../include/log/Logger.h"
#include "rpc_echo_client.h"
#include <boost/asio/io_context.hpp>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <memory>
#include <thread>

using namespace std::placeholders;
using namespace xrpc;

off_t kRollSize = 10 * 1000 * 1000;
logx::AsyncLogger *g_asyncLog = NULL;
void asyncOutput(const char *msg, int len) { g_asyncLog->append(msg, len); }

void on_echo(const echo::EchoResponse &response) {
    //
    LOG_DEBUG << "response: " << response.message();
}

void on_connect(const XError &error, std::shared_ptr<EchoService::rpc_echo_client> client) {
    LOG_DEBUG << error.to_string();

    echo::EchoRequest request;
    request.set_message("hello");
    client->echo(request, std::bind(&on_echo, std::placeholders::_1));
}

void test_async_client() {
    // logx::AsyncLogger log(::basename(__FILE__), kRollSize);
    // g_asyncLog = &log;
    // log.start();
    // logx::Logger::setOutput(asyncOutput);

    boost::asio::io_context netio;

    RPCClientrPtr rpcclient(new RPCClient(netio));
    std::shared_ptr<EchoService::rpc_echo_client> client(new EchoService::rpc_echo_client(rpcclient));

    uint64_t id = client->connect(std::bind(&on_connect, _1, client));
    assert(id == CONNECT_ID);

    netio.run();
}

void runNetIo(boost::asio::io_context &io) {
    LOG_INFO << "net io thread start";
    boost::asio::io_context::work work(io);
    io.run();
    LOG_DEBUG << "net io thread stop";
}

void test_sync_client() {
    logx::AsyncLogger log(::basename(__FILE__), kRollSize);
    g_asyncLog = &log;
    log.start();
    logx::Logger::setOutput(asyncOutput);

    boost::asio::io_context netio;
    boost::asio::io_context workio;

    RPCClientrPtr rpcclient(new RPCClient(netio));
    EchoService::rpc_echo_client client(rpcclient);
    // rpcclient->start();

    // XError error;
    // workio.post(std::bind(&EchoService::rpc_echo_client::connect, &client, std::ref(error)));
    XError error = defaultXError;
    workio.post([&client, &error]() {
        client.connect(error);
        LOG_INFO << error.to_string();
    });

    echo::EchoRequest request;
    request.set_message("hello");
    echo::EchoResponse response;
    // workio.post(std::bind(&EchoService::rpc_echo_client::echo, &client, std::ref(request), std::ref(response)));
    workio.post([&client, &request, &response]() {
        client.echo(request, response);
        LOG_DEBUG << "response: " << response.message();
    });

    // std::thread t1(&runNetIo, std::ref(netio));
    std::thread t1([&netio] {
        LOG_DEBUG << "net io thread start";
        boost::asio::io_context::work work(netio);
        netio.run();
        LOG_DEBUG << "net io thread stop";
    });

    std::thread t2([&workio] {
        LOG_DEBUG << "work io thread start";
        boost::asio::io_context::work work(workio);
        workio.run();
        LOG_DEBUG << "work io thread stop";
    });

    t1.join();
    t2.join();
}

int main() {
    // cout << __func__ << "," << __FUNCTION__ << endl;
    // std::string str = "echo_async";
    // size_t pos = str.find("_");
    // cout << str.substr(0, pos) << endl;
    logx::Logger::setLogLevel(Logger::DEBUG);

    test_async_client();
    // test_sync_client();

    return 0;
}