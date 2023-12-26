cmake_minimum_required(VERSION 3.5)

project(echo)

FIND_PACKAGE(Protobuf REQUIRED COMPONENTS protobuf)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../lib")

add_executable(rpcEchoClient echoClient.cpp echo.pb.cc rpc_EchoService_client.cpp)
target_link_libraries(rpcEchoClient 
    rpc net log utils 
    ssl crypto 
    boost_thread
    ${Protobuf_LIBRARIES} 
    ${Protobuf_LITE_LIBRARIES}
)

add_executable(rpcEchoServer echoServer.cpp echo.pb.cc rpc_EchoService_server.cpp)
target_link_libraries(rpcEchoServer 
    rpc net log utils 
    ssl crypto 
    boost_thread
    ${Protobuf_LIBRARIES} 
    ${Protobuf_LITE_LIBRARIES}
)