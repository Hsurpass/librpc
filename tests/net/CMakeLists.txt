# g++ main.cpp -Llib -lrpc -L/lib/x86_64-linux-gnu -lssl -lcrypto #版本太高
# g++ main.cpp -Llib -lrpc -L/usr/local/lib/ -lssl -lcrypto #1.1.1w

cmake_minimum_required(VERSION 3.5)

project(test1)

set(SRC main.cpp)

find_package(Boost REQUIRED)
message("BOOST_FOUND: " ${BOOST_FOUND})
find_package(OpenSSL)
# message("OpenSSL_FOUND: " ${OpenSSL_FOUND})

# include_directories(include)
link_directories(lib)
link_directories("/usr/local/lib/")

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} rpc 
    pthread 
    boost_system 
    ssl crypto
)