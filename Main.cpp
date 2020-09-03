#include <iostream>
#include <grpcpp/grpcpp.h>
#include <sstream>

#include "src/common/Logger.h"
#include "src/common/Container.h"
#include "src/ElectionServiceImpl.h"
#include "src/Configuration.h"

using namespace std;
using namespace rotr;
using namespace rotr::common;

int main(int argc, char* argv[]) {
    Container::I().logger = make_shared<Logger>("/tmp/rotr-svc-logs/rotr.log");
    auto logger = Container::I().logger;

    logger->info("\n\n            __ _                   _   _                           _        \n"
                 "           / _| |                 | | | |                         | |       \n"
                 " _ __ __ _| |_| |_    ___  _ __   | |_| |__   ___   _ __ ___   ___| | _____ \n"
                 "| '__/ _` |  _| __|  / _ \\| '_ \\  | __| '_ \\ / _ \\ | '__/ _ \\ / __| |/ / __|\n"
                 "| | | (_| | | | |_  | (_) | | | | | |_| | | |  __/ | | | (_) | (__|   <\\__ \\\n"
                 "|_|  \\__,_|_|  \\__|  \\___/|_| |_|  \\__|_| |_|\\___| |_|  \\___/ \\___|_|\\_\\___/\n"
                 "                                                                            \n"
                 "                                                                            ");

    // Command Line Params: --node-id rotr.1 --config-path <path-to-config>/server.yaml
    unique_ptr<Configuration> configuration = make_unique<Configuration>(argc, argv);

    stringstream electionServiceAddress;
    electionServiceAddress << configuration->curNodeConfig().host << ":" << configuration->curNodeConfig().electionPort;
    ElectionServiceImpl electionService;

    grpc::ServerBuilder electionServiceBuilder;
    electionServiceBuilder.AddListeningPort(electionServiceAddress.str(), grpc::InsecureServerCredentials());
    electionServiceBuilder.RegisterService(&electionService);
    unique_ptr<grpc::Server> electionServiceServer(electionServiceBuilder.BuildAndStart());

    logger->info("Node listening on port {} for election...", configuration->curNodeConfig().electionPort);
    electionServiceServer->Wait();
    return 0;
}