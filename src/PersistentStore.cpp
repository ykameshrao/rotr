//
// Created by ykameshrao on 3/7/19.
//

#include "PersistentStore.h"
#include "common/Container.h"

rotr::PersistentStore::PersistentStore(const shared_ptr<Configuration>& configuration) : _configuration {configuration} {
    _columnFamilies[CF::MAIN_QUEUE] = "MAIN_QUEUE";

    vector<string> mapValues;
    unordered_map<string, uint64_t> ttls;
    for (auto kv : _columnFamilies) {
        mapValues.push_back(kv.second);
        ttls[kv.second] = 1209600;
    }

    if (configuration->isCurrentNodeSeed()) {
        _columnFamilies[CF::META_INF] = "META_INF";
        ttls[_columnFamilies[CF::META_INF]] = 0;
    }

    _rdbClient = make_shared<RocksDBClient>(configuration->dataLocation(), mapValues, true, ttls);
}

string &rotr::PersistentStore::operator[](rotr::CF cf) {
    return _columnFamilies[cf];
}

string &rotr::PersistentStore::cf(rotr::CF cf) {
    return _columnFamilies[cf];
}

void rotr::PersistentStore::put(const string &columnFamily, const string &key, const string &data) {
    _rdbClient->putInCF(columnFamily, key, data);
}

string &&rotr::PersistentStore::get(const string &columnFamily, const string &key) {
    string val;
    _rdbClient->getInCF(columnFamily, key, val);
    return move(val);
}
