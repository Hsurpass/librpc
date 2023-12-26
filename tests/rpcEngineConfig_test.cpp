#include "gtest/gtest.h"

// #include "RpcEngineConfig.h"
#include "../include/RpcEngineConfig.h"

#include <iostream>
#include <string>

using namespace std;

class RpcEngineConfig_test : public testing::Test {
public:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(RpcEngineConfig_test, config) {
    // std::string path("../config/rpcConfig.ini");
    std::string path = "rpcConfig.ini";
    xrpc::RpcEngineConfig::createInstanceWithFilePath(path);

    EXPECT_EQ(xrpc::RpcEngineConfig::getInstance()->logLevel(), "debug");
}

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
