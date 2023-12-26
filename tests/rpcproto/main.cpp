#include "rpc.pb.h"
#include <iostream>

using namespace std;

int main() {

    xrpc::RpcMessage rpcm;
    rpcm.set_id(1);
    rpcm.SerializeAsString();

    return 0;
}
