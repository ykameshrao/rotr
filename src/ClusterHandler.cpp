//
// Created by ykameshrao on 5/7/19.
//

#include <sstream>
#include "ClusterHandler.h"
#include "common/Utils.h"

rotr::ClusterHandler::ClusterHandler(const shared_ptr<Configuration>& configuration,
        const shared_ptr<PersistentStore>& persistentStore) : _configuration{configuration}, _persistentStore{persistentStore} {
}

void rotr::ClusterHandler::setup(const string &clusterId, const string &ip, const string &port) {
    stringstream key;
    key << "ClusterId-" << clusterId << "-CurrentNode";
    stringstream value;
    value << ip << ":" << port;
    _persistentStore->put(_persistentStore->cf(CF::META_INF), key.str(), value.str());
}

void rotr::ClusterHandler::addNode(const string &clusterId, const string &ip, const string &port) {
    auto allNodes = getAllNodes(clusterId);
    allNodes.push_back(make_pair(ip, port));

    stringstream key;
    key << "ClusterId-" << clusterId << "-AllNodes";

    putSerializedNodeList(key, allNodes);
}

void rotr::ClusterHandler::addSeedNode(const string &clusterId, const string &ip, const string &port) {
    auto allSeedNodes = getAllSeedNodes(clusterId);
    allSeedNodes.push_back(make_pair(ip, port));

    stringstream key;
    key << "ClusterId-" << clusterId << "-SeedNodes";

    putSerializedNodeList(key, allSeedNodes);
}

vector<pair<string, string>> &&rotr::ClusterHandler::getAllNodes(const string &clusterId) {
    stringstream key;
    key << "ClusterId-" << clusterId << "-AllNodes";

    return getDeserializedNodeList(key);
}


vector<pair<string, string>> &&rotr::ClusterHandler::getAllSeedNodes(const string &clusterId) {
    stringstream key;
    key << "ClusterId-" << clusterId << "-SeedNodes";

    return getDeserializedNodeList(key);
}

vector<pair<string, string>> &&rotr::ClusterHandler::getDeserializedNodeList(const stringstream &key) {
    string response = _persistentStore->get(_persistentStore->cf(rotr::META_INF), key.str());
    if (response.empty())
        return move(vector<pair<string, string>>());
    else {
        vector<pair<string, string>> result;
        vector<string> allNodeAddrs;
        Utils::tokenize(response, ",", allNodeAddrs);
        for (string na : allNodeAddrs) {
            vector<string> addr;
            pair<string, string> p;
            Utils::tokenize(na, ":", addr);
            p.first = addr[0];
            p.second = addr[1];
            result.push_back(p);
        }

        return move(result);
    }
}

void rotr::ClusterHandler::putSerializedNodeList(const stringstream &key, const vector<pair<string, string>> &values) {
    stringstream val;
    for (auto p : values) {
        val << p.first << ":" << p.second << ",";
    }

    _persistentStore->put(_persistentStore->cf(rotr::META_INF), key.str(), val.str());
}