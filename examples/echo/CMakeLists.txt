cmake_minimum_required(VERSION 3.5)

project(echo)

find_package(OpenSSL REQUIRED)
message("OPENSSL_FOUND: " ${OPENSSL_FOUND})
message("OPENSSL_INCLUDE_DIR: " ${OPENSSL_INCLUDE_DIR})
message("OPENSSL_LIBRARIES: " ${OPENSSL_LIBRARIES})

FIND_PACKAGE(Protobuf REQUIRED COMPONENTS protobuf)
message("PROTOBUF_FOUND: " ${PROTOBUF_FOUND})
message("PROTOBUF_INCLUDE_DIR: " ${PROTOBUF_INCLUDE_DIR})
message("PROTOBUF_LIBRARIES: " ${PROTOBUF_LIBRARIES})

# execute_process(COMMAND bash -c "protoc -I. --cpp_out=${CMAKE_CURRENT_SOURCE_DIR} echo.proto")
# protobuf_generate_cpp(PROTO_SRC PROTO_HEADER echo.proto)  

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../lib")

add_executable(rpcEchoClient 
    echoClient.cpp 
    echo.pb.cc 
    rpc_EchoService_client.cpp
)
target_link_libraries(rpcEchoClient 
    # utils 
    # log 
    # net
    rpc 
    boost_thread
    ${Protobuf_LIBRARIES} 
    ${Protobuf_LITE_LIBRARIES}
    ssl 
    crypto 
)

add_executable(rpcEchoServer 
    echoServer.cpp 
    echo.pb.cc 
    rpc_EchoService_server.cpp
)
target_link_libraries(rpcEchoServer 
    rpc 
    # net 
    # log 
    # utils 
    boost_thread
    ${Protobuf_LIBRARIES} 
    ${Protobuf_LITE_LIBRARIES}
    ssl 
    crypto 
)