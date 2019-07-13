//
// Created by ykameshrao on 28/2/19.
//

#ifndef ROTR_INMEMORYSTORE_H
#define ROTR_INMEMORYSTORE_H

#include <unordered_map>

#include "proto/generated/rotr.pb.h"
#include "proto/generated/rotr.grpc.pb.h"
#include "common/RocksDBClient.h"

using namespace std;

namespace rotr {
    /**
     * Will store the message and other related data for channels active on the broker instance.
     * The channels, their messages, per channel offsets, channel offsets, consumer offsets
     */
    class InMemoryStore {
    public:
        InMemoryStore(const InMemoryStore &) = delete;
        InMemoryStore &operator=(const InMemoryStore &) = delete;
        InMemoryStore(InMemoryStore &&) = delete;
        InMemoryStore &operator=(InMemoryStore &&) = delete;

    private:

    };
}

#endif //ROTR_INMEMORYSTORE_H
