cmake_minimum_required(VERSION 3.13)
project(rotr)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)

# Clang exports C++17 in std::experimental namespace (tested on Clang 5 and 6).
# This gives an error on date.h external library.
# Following workaround forces Clang to compile at best with C++14
if(COMPILER_SUPPORTS_CXX17 AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
elseif(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

# Find Protobuf installation
find_package(Protobuf REQUIRED)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

link_libraries(grpc++_unsecure grpc gpr pthread ${PROTOBUF_LIBRARY} rocksdb)

file(GLOB_RECURSE SOURCE_FILES "src/**")
file(GLOB_RECURSE COMMON_SOURCE_FILES "src/common/**")
file(GLOB_RECURSE PBF_SOURCE_FILES "src/proto/**")
set(SOURCE ${SOURCE_FILES} ${COMMON_SOURCE_FILES} ${PBF_SOURCE_FILES} Main.cpp src/Node.cpp src/Node.h)

set(MODULE_NAME "rotr")
add_executable(${MODULE_NAME} ${SOURCE})

# Install cmake - https://cmake.org/install/
# Install protobuf - https://github.com/protocolbuffers/protobuf/tree/master/src
# Install grpc - https://github.com/grpc/grpc/tree/v1.15.0/src/cpp
# Install rocksdb - https://github.com/facebook/rocksdb/blob/master/INSTALL.md
# Install spdlog - https://github.com/gabime/spdlog#benchmarks (apt-get install libspdlog-dev)
# Install yaml-cpp - https://github.com/jbeder/yaml-cpp.git



# Install evpp - https://github.com/Qihoo360/evpp/blob/master/docs/quick_start.md
# Install libevent - https://github.com/libevent/libevent
# Install evpp - https://github.com/Qihoo360/evpp - refer the getting started here. Requires installation of libevent, boost, glog, gflags
# Install glog - https://github.com/google/glog
# Install libevhtp - https://github.com/criticalstack/libevhtp/releases
# C++ Wrapper for LibEvent - https://kukuruku.co/post/lightweight-http-server-in-less-than-40-lines-on-libevent-and-c-11/
# C++ Wrapper for LibEvent lev - https://github.com/YasserAsmi/lev
# Install libuv - https://github.com/libuv/libuv
# Install libSourcey - c++ wrapper on libuv - https://github.com/sourcey/libsourcey, https://github.com/sourcey/libsourcey/releases
# Install http_parser - https://github.com/nodejs/http-parser
# Install uvw - https://github.com/skypjack/uvw
# Important example in libsource http: https://github.com/sourcey/libsourcey/issues/219
# Install Mif - https://github.com/tdv/mif
# Isntall boost - https://www.boost.org/doc/libs/1_69_0/more/getting_started/unix-variants.html
# Isntall flatbuffers - https://google.github.io/flatbuffers/flatbuffers_guide_building.html
# Install folly, dependencies - https://github.com/facebook/folly
# Install fizz - https://github.com/facebookincubator/fizz
# Install wangle - https://github.com/facebook/wangle