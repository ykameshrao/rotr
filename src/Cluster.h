//
// Created by ykameshrao on 5/7/19.
//

#ifndef ROTR_CLUSTER_H
#define ROTR_CLUSTER_H

#include <memory>
#include <sstream>
#include <grpcpp/grpcpp.h>

#include "common/Container.h"
#include "ReplicationServiceImpl.h"
#include "Configuration.h"
#include "PersistentStore.h"

namespace rotr {
    /**
     * Class to deal with the logic for discovering and managing the cluster participation of the node.
     */
    class Cluster {
        const shared_ptr <Configuration> _configuration;
        const shared_ptr <PersistentStore> _persistentStore;

    public:
        Cluster(const shared_ptr <Configuration> &configuration, const shared_ptr <PersistentStore> &persistentStore)
                : _configuration{configuration}, _persistentStore{persistentStore} {}
        Cluster(const Cluster &) = delete;
        Cluster &operator=(const Cluster &) = delete;
        Cluster(Cluster &&) = delete;
        Cluster &operator=(Cluster &&) = delete;

        void clusterServiceThread();
        void nodeGossipThread();
    };
}

#endif //ROTR_CLUSTER_H
