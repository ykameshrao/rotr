//
// Created by ykameshrao on 3/7/19.
//

#ifndef ROTR_PERSISTENTSTORE_H
#define ROTR_PERSISTENTSTORE_H

#include <iostream>
#include "common/RocksDBClient.h"
#include "Configuration.h"

using namespace std;
using namespace rotr::common;

namespace rotr {
    enum CF {
        META_INF = 0,
        MAIN_QUEUE
    };

    class PersistentStore {
    private:
        shared_ptr<Configuration> _configuration;
        shared_ptr<RocksDBClient> _rdbClient;
        unordered_map<CF, string> _columnFamilies;
    public:
        PersistentStore(const shared_ptr<Configuration> &configuration);
        PersistentStore(const PersistentStore &) = delete;
        PersistentStore & operator=(const PersistentStore &) = delete;
        PersistentStore(PersistentStore &&) = delete;
        PersistentStore & operator=(PersistentStore &&) = delete;

        string &operator[](CF cf);
        string &cf(CF cf);
        void put(const string &columnFamily, const string &key, const string &data);
        string &&get(const string &columnFamily, const string &key);
    };
}


#endif //ROTR_PERSISTENTSTORE_H
