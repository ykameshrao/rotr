//
// Created by ykameshrao on 5/7/19.
//

#ifndef ROTR_CLUSTERHANDLER_H
#define ROTR_CLUSTERHANDLER_H

#include "PersistentStore.h"

namespace rotr {
    class ClusterHandler {
    private:
        shared_ptr<Configuration> _configuration;
        shared_ptr<PersistentStore> _persistentStore;

        void putSerializedNodeList(const stringstream &key, const vector<pair<string, string>> &values);
        vector<pair<string, string>> &&getDeserializedNodeList(const stringstream &key);
    public:
        ClusterHandler(const shared_ptr<Configuration>& configuration,
                       const shared_ptr<PersistentStore>& persistentStore);
        ClusterHandler(const ClusterHandler &) = delete;
        ClusterHandler &operator=(const ClusterHandler &) = delete;

        void setup(const string& clusterId, const string& ip, const string& port);
        void addNode(const string& clusterId, const string& ip, const string& port);
        void addSeedNode(const string& clusterId, const string& ip, const string& port);
        vector<pair<string, string>> &&getAllNodes(const string& clusterId);
        vector<pair<string, string>> &&getAllSeedNodes(const string& clusterId);
    };
}


#endif //ROTR_CLUSTERHANDLER_H
