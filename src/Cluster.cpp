//
// Created by ykameshrao on 5/7/19.
//

#include "Cluster.h"

using namespace std;
using namespace rotr::common;
using namespace rotr;

void Cluster::clusterServiceThread() {
    auto logger = rotr::common::Container::I().logger;
    unique_ptr<ClusterHandler> clusterHandler = make_unique<ClusterHandler>(_configuration, _persistentStore);
    clusterHandler->setup(_configuration->clusterId(), _configuration->ip(), _configuration->port());

    logger->info("Starting the cluster service on the same port...{}", _configuration->port());
    ReplicationServiceImpl clusterService(move(clusterHandler));
    grpc::ServerBuilder builder;

    stringstream serverAddress;
    serverAddress << _configuration->ip() << ":" << _configuration->port();
    builder.AddListeningPort(serverAddress.str(), grpc::InsecureServerCredentials());
    builder.RegisterService(&clusterService);
    unique_ptr<grpc::Server> server(builder.BuildAndStart());

    logger->info("ClusterService listening on port {}...", _configuration->port());
    server->Wait();
}

void Cluster::nodeGossipThread() {
    auto logger = rotr::common::Container::I().logger;
    logger->info("Node gossip to cluster seed node ...");
}
