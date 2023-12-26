#pragma once

#include "net/commonType.h"
#include "net/netCommon.h"
#include "rpc.pb.h"
#include <memory>
#include <string>

namespace xrpc {
using namespace net;

enum XErrorCode {
    XNONE = 0, //
    XCONNECT_OK = 1,
    XCONNECT_FAIL,
    XNOT_CONNECTED,
    XDISCONNECT_OK,
    XERRORCODE_NUM
};

typedef struct XError {
    XErrorCode errorCode;
    std::string errorMessage;

    std::string to_string() const;
} XError;

extern XError defaultXError;
extern XError make_XError(XErrorCode code);

static const uint64_t CONNECT_ID = 1;
static const uint64_t DISCONNECT_ID = 2;

static const std::string CONNECT_FUNC = "connect";
static const std::string DISCONNECT_FUNC = "disconnect";

typedef std::shared_ptr<RpcMessage> RpcMessagePtr;
void makeRPCResponse(ByteArray &bytes, ::google::protobuf::Message *response, uint64_t id);

typedef std::function<void(const std::string &func, const std::string &)> NotifyFunc; //通知接口

typedef std::function<MessagePtr(const std::string &param, uint64_t id, TcpConnectionPtr connection)> StubFunc;
typedef std::unordered_map<std::string, StubFunc> StubFuncTable;

class RPCRequestProcessor;
typedef std::shared_ptr<RPCRequestProcessor> RPCRequestProcessorPtr;
typedef std::weak_ptr<RPCRequestProcessor> RPCRequestProcessorWeakPtr;

class Result;
typedef std::shared_ptr<Result> ResultPtr;
typedef std::function<void(const std::string &, const XError &error)> ResultCallback;

class RPCConnection;
typedef std::shared_ptr<RPCConnection> RPCConnectionPtr;

class RPCConnector;
typedef std::shared_ptr<RPCConnector> RPCConnectorPtr;

class RPCClient;
typedef std::shared_ptr<RPCClient> RPCClientrPtr;
typedef std::weak_ptr<RPCClient> RPCClientrWeakPtr;

class RPCAcceptor;
typedef std::shared_ptr<RPCAcceptor> RPCAcceptorPtr;

class RPCServer;
typedef std::shared_ptr<RPCServer> RPCServerPtr;
typedef std::weak_ptr<RPCServer> RPCServerWeakPtr;

} // namespace xrpc