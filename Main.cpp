#include <iostream>
#include <grpcpp/grpcpp.h>
#include <sstream>

#include "src/common/Logger.h"
#include "src/common/Container.h"
#include "src/RaftInternalRPCServiceImpl.h"
#include "src/Configuration.h"

using namespace std;
using namespace rotr;
using namespace rotr::common;

int main(int argc, char* argv[]) {
    Container::I().logger = std::make_shared<Logger>("rotr.log");
    auto logger = Container::I().logger;

    logger->info("\n\n            __ _                   _   _                           _        \n"
                 "           / _| |                 | | | |                         | |       \n"
                 " _ __ __ _| |_| |_    ___  _ __   | |_| |__   ___   _ __ ___   ___| | _____ \n"
                 "| '__/ _` |  _| __|  / _ \\| '_ \\  | __| '_ \\ / _ \\ | '__/ _ \\ / __| |/ / __|\n"
                 "| | | (_| | | | |_  | (_) | | | | | |_| | | |  __/ | | | (_) | (__|   <\\__ \\\n"
                 "|_|  \\__,_|_|  \\__|  \\___/|_| |_|  \\__|_| |_|\\___| |_|  \\___/ \\___|_|\\_\\___/\n"
                 "                                                                            \n"
                 "                                                                            ");

    //--start-at 0.0.0.0:50051 --data-dir-path /tmp/rotr --cluster-id Local
    unique_ptr<Configuration> configuration = make_unique<Configuration>(argc, argv);

    stringstream serverAddress;
    serverAddress << configuration->ip() << ":" << configuration->port();
    RaftInternalRPCServiceImpl raftInternalRpcService;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverAddress.str(), grpc::InsecureServerCredentials());
    builder.RegisterService(&raftInternalRpcService);
    unique_ptr<grpc::Server> server(builder.BuildAndStart());

    logger->info("Node listening on port {}...", configuration->ip());
    server->Wait();
    return 0;
}