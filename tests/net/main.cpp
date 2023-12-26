#include "include/TcpSocket.h"

#include <iostream>

using namespace std;

int main() {
    net::TcpScoket::makeTcpSocket(nullptr);
    cout << "hello" << endl;
    return 0;
}