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
    vector<pair<string, string>> allNodes;
    getAllNodes(clusterId, allNodes);
    allNodes.push_back(make_pair(ip, port));

    stringstream key;
    key << "ClusterId-" << clusterId << "-AllNodes";

    putSerializedNodeList(key, allNodes);
}

void rotr::ClusterHandler::addSeedNode(const string &clusterId, const string &ip, const string &port) {
    vector<pair<string, string>> allSeedNodes;
    getAllNodes(clusterId, allSeedNodes);
    allSeedNodes.push_back(make_pair(ip, port));

    stringstream key;
    key << "ClusterId-" << clusterId << "-SeedNodes";

    putSerializedNodeList(key, allSeedNodes);
}

void rotr::ClusterHandler::getAllNodes(const string &clusterId, vector<pair<string, string>> &val) {
    stringstream key;
    key << "ClusterId-" << clusterId << "-AllNodes";
    getDeserializedNodeList(key, val);
}


void rotr::ClusterHandler::getAllSeedNodes(const string &clusterId, vector<pair<string, string>> &val) {
    stringstream key;
    key << "ClusterId-" << clusterId << "-SeedNodes";
    getDeserializedNodeList(key, val);
}

void rotr::ClusterHandler::getDeserializedNodeList(const stringstream &key, vector<pair<string, string>> &val) {
    string response;
    _persistentStore->get(_persistentStore->cf(rotr::META_INF), key.str(), response);
    if (response.empty())
        throw "key not found";
    else {
        vector<string> allNodeAddrs;
        Utils::tokenize(response, ",", allNodeAddrs);
        for (string na : allNodeAddrs) {
            vector<string> addr;
            pair<string, string> p;
            Utils::tokenize(na, ":", addr);
            p.first = addr[0];
            p.second = addr[1];
            val.push_back(p);
        }
    }
}

void rotr::ClusterHandler::putSerializedNodeList(const stringstream &key, const vector<pair<string, string>> &values) {
    stringstream val;
    for (auto p : values) {
        val << p.first << ":" << p.second << ",";
    }

    _persistentStore->put(_persistentStore->cf(rotr::META_INF), key.str(), val.str());
}