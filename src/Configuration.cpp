//
// Created by kamesh on 30/6/19.
//

#include "Configuration.h"
#include "common/anyoption.h"
#include "common/Container.h"
#include "common/Utils.h"

using namespace rotr::common;

rotr::Configuration::Configuration(int argc, char **argv) {
    auto logger = Container::I().logger;
    unique_ptr<AnyOption> opt = make_unique<AnyOption>();

    opt->noPOSIX();
    opt->autoUsagePrint(true);
    opt->setVerbose();

    opt->addUsage("Usage: ");
    opt->addUsage("");
    opt->addUsage("--start-at\t\t\t\tip:port based address to start this broker at");
    opt->addUsage("--data-dir-path \t\tData storage location");
    opt->addUsage("--cluster-id \t\t\tUser defined identifier for the cluster");
    opt->addUsage("--config-path \t\t\tUser defined yaml based configuration for the cluster");

    opt->setOption("start-at");
    opt->setOption("data-dir-path");
    opt->setOption("cluster-id");
    opt->setOption("config-path");

    opt->processCommandArgs(argc, argv);

    if (!opt->hasOptions()) { /* print usage if no options */
        opt->printUsage();
        exit(-1);
    }


    vector<string> localAddr;
    Utils::tokenize(opt->getValue("start-at"), ":", localAddr);
    _ip = localAddr[0];
    _port = localAddr[1];
    _dataDirPath = opt->getValue("data-dir-path");
    _clusterId = opt->getValue("cluster-id");

    logger->info("Node be reachable at : {}", opt->getValue("start-at"));
    logger->info("Node data dir at : {}", opt->getValue("data-dir-path"));
    logger->info("ClusterId : {}", opt->getValue("cluster-id"));
}
