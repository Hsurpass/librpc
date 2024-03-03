cmake_minimum_required(VERSION 3.5)

project(RPCEngineTests)

message(STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})

find_package(Boost REQUIRED)
find_package(GTest REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
message("--------------- GTest_FOUND: " ${GTest_FOUND})
message("--------------- GTEST_INCLUDE_DIRS: " ${GTEST_INCLUDE_DIRS})
message("--------------- GTEST_LIBRARIES: " ${GTEST_LIBRARIES}) 


FIND_PACKAGE(Protobuf REQUIRED COMPONENTS protobuf)
#FIND_PACKAGE(Protobuf REQUIRED CONFIG COMPONENTS protobuf)

MESSAGE(STATUS "Protobuf_FOUND:" ${Protobuf_FOUND})
MESSAGE(STATUS "Protobuf_VERSION:" ${Protobuf_VERSION})
message("Protobuf_INCLUDE_DIRS: " ${Protobuf_INCLUDE_DIRS})
message("Protobuf_LIBRARIES: " ${Protobuf_LIBRARIES})
message("Protobuf_PROTOC_LIBRARIES: " ${Protobuf_PROTOC_LIBRARIES})
message("Protobuf_LITE_LIBRARIES: " ${Protobuf_LITE_LIBRARIES})

execute_process(COMMAND bash -c "protoc -I. --cpp_out=${CMAKE_CURRENT_SOURCE_DIR} echorpc.proto")
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER echorpc.proto)  

# find_package(GMock REQUIRED)
# find_package(absl REQUIRED)

# include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib")

add_executable(rpcEngineConfig_test rpcEngineConfig_test.cpp)
target_link_libraries(rpcEngineConfig_test rpc ${GTEST_LIBRARIES} pthread)


# utils
add_executable(timestamp_test utils/timestamp_test.cpp)
target_link_libraries(timestamp_test utils)

add_executable(timezone_test utils/timezone_test.cpp)
target_link_libraries(timezone_test utils)

add_executable(date_test utils/date_test.cpp)
target_link_libraries(date_test utils)

add_executable(threadpool_test utils/threadpool_test.cpp)
target_link_libraries(threadpool_test log utils)


# log
add_executable(logstream_test log/logstream_test.cpp)
target_link_libraries(logstream_test log boost_unit_test_framework)

add_executable(logfile_test log/logfile_test.cpp)
target_link_libraries(logfile_test log utils)

add_executable(logger_test log/logger_test.cpp)
target_link_libraries(logger_test log utils)

add_executable(asynclogger_test log/asynclogger_test.cpp)
target_link_libraries(asynclogger_test log utils)

# net
add_executable(tcpserver_test net/tcpserver_test.cpp)
target_link_libraries(tcpserver_test net log utils ssl crypto)

add_executable(tcpclient_test net/tcpclient_test.cpp)
target_link_libraries(tcpclient_test net log utils ssl crypto)

add_executable(echo_tcpclient net/echo_tcpclient.cpp)
target_link_libraries(echo_tcpclient net log utils ssl crypto)

add_executable(echo_tcpserver net/echo_tcpserver.cpp)
target_link_libraries(echo_tcpserver net log utils ssl crypto)

#engine
add_executable(rpc_echo_client 
    test_echo_rpc_client.cpp 
    rpc_echo_client.cpp 
    echorpc.pb.cc
)
target_link_libraries(rpc_echo_client 
    rpc net log utils  
    boost_thread
    ${Protobuf_LIBRARIES} 
    ${Protobuf_LITE_LIBRARIES}
    ssl crypto
)

add_executable(rpc_echo_server 
    test_echo_rpc_server.cpp 
    rpc_echo_server.cpp 
    echorpc.pb.cc
)
target_link_libraries(rpc_echo_server 
    rpc net log utils 
    boost_thread
    ${Protobuf_LIBRARIES} 
    ${Protobuf_LITE_LIBRARIES}
    ssl crypto 
)


enable_testing()

file(COPY ../config/rpcConfig.ini DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME rpcEngineConfig_test COMMAND rpcEngineConfig_test)

add_test(NAME logstream_test COMMAND logstream_test)


