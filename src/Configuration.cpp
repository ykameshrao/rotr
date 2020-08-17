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
    opt->addUsage("--node-id \t\t\tUser defined identifier for the node from the configured list of nodes");
    opt->addUsage("--config-path \t\t\tUser defined yaml based configuration for the cluster");

    opt->setOption("node-id");
    opt->setOption("config-path");

    opt->processCommandArgs(argc, argv);

    if (!opt->hasOptions()) { /* print usage if no options */
        opt->printUsage();
        exit(-1);
    }

    _nodeId = opt->getValue("node-id");
    _configPath = opt->getValue("config-path");

    //logger->info("Node be reachable at : {}", opt->getValue("start-at"));
    //logger->info("Node data dir at : {}", opt->getValue("data-dir-path"));
    //logger->info("ClusterId : {}", opt->getValue("cluster-id"));
}
