//
// Created by ykameshrao on 03/11/20.
//

#include "RotrApp.h"
#include "common/Container.h"
#include "ReplicationServiceImpl.h"
#include "RotrServiceImpl.h"

rotr::RotrApp::RotrApp(int argc, char **argv) {
    _configuration = make_unique<Configuration>(argc, argv);
}

void rotr::RotrApp::startElectionServiceThread() {
    _electionServiceThread.reset(new thread([this]() {
        auto logger = common::Container::I().logger;
        stringstream electionServiceAddress;
        electionServiceAddress << _configuration->curNodeConfig().host << ":"
                               << _configuration->curNodeConfig().electionPort;
        ElectionServiceImpl electionService;

        grpc::ServerBuilder electionServiceBuilder;
        electionServiceBuilder.AddListeningPort(electionServiceAddress.str(), grpc::InsecureServerCredentials());
        electionServiceBuilder.RegisterService(&electionService);
        unique_ptr<grpc::Server> electionServiceServer(electionServiceBuilder.BuildAndStart());

        logger->info("Node listening on port {} for election...", _configuration->curNodeConfig().electionPort);
        electionServiceServer->Wait();
    }));
}

void rotr::RotrApp::startReplicationServiceThread() {
    _replicationServiceThread.reset(new thread([this]() {
        auto logger = common::Container::I().logger;
        stringstream replicationServiceAddress;
        replicationServiceAddress << _configuration->curNodeConfig().host << ":"
                               << _configuration->curNodeConfig().replicationPort;
        ReplicationServiceImpl replicationService;

        grpc::ServerBuilder replicationServiceBuilder;
        replicationServiceBuilder.AddListeningPort(replicationServiceAddress.str(), grpc::InsecureServerCredentials());
        replicationServiceBuilder.RegisterService(&replicationService);
        unique_ptr<grpc::Server> replicationServiceServer(replicationServiceBuilder.BuildAndStart());

        logger->info("Node listening on port {} for replication...", _configuration->curNodeConfig().replicationPort);
        replicationServiceServer->Wait();
    }));
}

void rotr::RotrApp::startRotrServiceThread() {
    _rotrServiceThread.reset(new thread([this]() {
        auto logger = common::Container::I().logger;
        stringstream rotrServiceAddress;
        rotrServiceAddress << _configuration->curNodeConfig().host << ":"
                               << _configuration->curNodeConfig().rotrPort;
        RotrServiceImpl rotrService;

        grpc::ServerBuilder rotrServiceBuilder;
        rotrServiceBuilder.AddListeningPort(rotrServiceAddress.str(), grpc::InsecureServerCredentials());
        rotrServiceBuilder.RegisterService(&rotrService);
        unique_ptr<grpc::Server> rotrServiceServer(rotrServiceBuilder.BuildAndStart());

        logger->info("Node listening on port {} for rotr...", _configuration->curNodeConfig().rotrPort);
        rotrServiceServer->Wait();
    }));
}

void rotr::RotrApp::startApp() {
    startElectionServiceThread();
    startReplicationServiceThread();
    startRotrServiceThread();
}

void rotr::RotrApp::joinAllThreadsAndWait() {
    _electionServiceThread->join();
    _replicationServiceThread->join();
    _rotrServiceThread->join();
}
