### ROTR - Raft On The RocksDB
rotr is the C++14 Raft consensus protocol implementation using RocksDB as storage solution.

#### Code Setup:

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
    
    CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=/home/<user-name>/vcpkg/scripts/buildsystems/vcpkg.cmake"

How to use VCPKG with CLion
What Yoav tried to say is this: VCPKG provides a .cmake file to be used during configuration process, so that CMake can correctly recognize the needed libraries' paths. A good advice of its usage with CLion's cmake was found here ( https://github.com/Microsoft/vcpkg/issues/3572 ):

    Go to File -> Settings -> Build, Execution, Deployment -> CMake
    Choose one profile, and then find "CMake Options".
    Insert value to the option: -DCMAKE_TOOLCHAIN_FILE=<path_to_vcpkg>/scripts/buildsystems/vcpkg.cmake


