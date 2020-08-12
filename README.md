ROTR - Raft On The RocksDB

rotr is the C++14 Raft consensus protocol implementation using RocksDB as storage solution.

Installation:
`
# install vcpkg package manager on your system using the official instructions
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install

vcpkg install protobuf
vcpkg install grpc
vcpkg install rocksdb
vcpkg install yaml-cpp
vcpkg install spdlog
`