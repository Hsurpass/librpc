#include "rpc_echo_client.h"

namespace EchoService {

rpc_echo_client::rpc_echo_client(RPCClientrPtr client) : m_rpcClient(client) {}

std::string rpc_echo_client::request(const std::string &func, MessagePtr request, XError &error) {
    return m_rpcClient->requestSync(func, request, error);
}

uint64_t rpc_echo_client::request(const std::string &func, MessagePtr request, const ResultCallback &cb) {
    return m_rpcClient->requestAsync(func, request, cb);
}

void rpc_echo_client::connect(XError &error) {
    if (!m_rpcClient) {
        error.errorCode = XNOT_CONNECTED;
        error.errorMessage = "rpc client is NULL";
        return;
    }

    request(__func__, MessagePtr(), error);
    LOG_DEBUG << "finish connect";
    if (error.errorCode != XCONNECT_OK) {
        LOG_ERROR << error.to_string();
    }
}

uint64_t rpc_echo_client::connect(const connectCallBack &callback) {
    connectCallBackPtr cb(new connectCallBack(callback));
    if (m_rpcClient) {
        return request(__func__, MessagePtr(), std::bind(&rpc_echo_client::on_connect, this, _1, _2, cb));
    } else {
        XError error;
        error.errorCode = XNOT_CONNECTED;
        error.errorMessage = "rpc client is NULL";
        on_connect("", error, cb);
        return 0;
    }
}

void rpc_echo_client::on_connect(const std::string &response, const XError &error, connectCallBackPtr cb) {
    if (cb) {
        (*cb)(error);
    } else {
        if (error.errorCode != xrpc::XCONNECT_OK) {
            LOG_ERROR << error.to_string();
        }
    }
}

void rpc_echo_client::disConnect(XError &error) {
    if (!m_rpcClient) {
        error.errorCode = XNOT_CONNECTED;
        error.errorMessage = "rpc client is NULL";
        return;
    }

    request(__func__, MessagePtr(), error);
    LOG_DEBUG << "finish disconnect";
    if (error.errorCode != XDISCONNECT_OK) {
        LOG_ERROR << error.to_string();
    }
}

uint64_t rpc_echo_client::disConnect(const disConnectCallBack &callback) {
    disConnectCallBackPtr cb(new disConnectCallBack(callback));
    if (m_rpcClient) {
        return request(__func__, MessagePtr(), std::bind(&rpc_echo_client::on_disconnect, this, _1, _2, cb));
    } else {
        XError error;
        error.errorCode = XDISCONNECT_OK;
        error.errorMessage = "rpc client is NULL";
        on_disconnect("", error, cb);
        return 0;
    }
}

void rpc_echo_client::on_disconnect(const std::string &response, const XError &error, connectCallBackPtr cb) {
    if (cb) {
        (*cb)(error);
    } else {
        if (error.errorCode != xrpc::XDISCONNECT_OK) {
            LOG_ERROR << error.to_string();
        }
    }
}

void rpc_echo_client::subcribe(const SubScribeRequest &request_, SubScribeResponse &response) {
    MessagePtr req(new SubScribeRequest(request_));

    LOG_DEBUG << "send subscribe";
    XError error;
    std::string res = request(__func__, req, error);

    if (response.ParseFromString(res)) {
        return;
    } else {
        LOG_ERROR << "response parse failed !!! error: " << error.to_string();
    }
}

uint64_t rpc_echo_client::subscribe(const SubScribeRequest &request_, const subscribeCallBack &callback) {
    subscribeCallBackPtr cb(new subscribeCallBack(callback));
    if (m_rpcClient) {
        MessagePtr req(new SubScribeRequest(request_));
        return request(__func__, req, std::bind(&rpc_echo_client::on_subscribe, this, _1, _2, cb));
    } else {
        XError error;
        error.errorCode = XNOT_CONNECTED;
        error.errorMessage = "rpc client is NULL";
        on_subscribe("", error, cb);
        return 0;
    }
}

void rpc_echo_client::on_subscribe(const std::string &response, const XError &error, subscribeCallBackPtr cb) {
    SubScribeResponse res;
    if (res.ParseFromString(response)) {
        if (cb) {
            (*cb)(res);
        }
    } else {
        LOG_ERROR << "response parse failed !!! error: " << error.to_string();
    }
}

void rpc_echo_client::echo(const echo::EchoRequest &request_, echo::EchoResponse &response) {
    MessagePtr req(new echo::EchoRequest(request_));

    LOG_DEBUG << "send request";
    XError error;
    std::string res = request(__func__, req, error);

    if (response.ParseFromString(res)) {
        return;
    } else {
        LOG_ERROR << "response parse failed !!! error: " << error.to_string();
    }
}

uint64_t rpc_echo_client::echo(const echo::EchoRequest &request_, const echoCallBack &callback) {
    echoCallBackPtr cb(new echoCallBack(callback));
    if (m_rpcClient) {
        MessagePtr req(new echo::EchoRequest(request_));
        return request(__func__, req, std::bind(&rpc_echo_client::on_echo, this, _1, _2, cb));
    } else {
        XError error;
        error.errorCode = XNOT_CONNECTED;
        error.errorMessage = "rpc client is NULL";
        on_echo("", error, cb);
        return 0;
    }
}

void rpc_echo_client::on_echo(const std::string &response, const XError &error, echoCallBackPtr cb) {
    echo::EchoResponse res;
    if (res.ParseFromString(response)) {
        if (cb) {
            (*cb)(res);
        }
    } else {
        LOG_ERROR << "response parse failed !!! error: " << error.to_string();
    }
}

} // namespace EchoService
