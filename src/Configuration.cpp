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
    opt->addUsage("--seeds\t\t\t\t\tComma separated list of ip:port combination for network discovery");
    opt->addUsage("--data-dir-path \t\tData storage location");

    opt->setOption("start-at");
    opt->setOption("seeds");
    opt->setOption("data-dir-path");

    opt->processCommandArgs(argc, argv);

    if (!opt->hasOptions()) { /* print usage if no options */
        opt->printUsage();
        exit(-1);
    }

    vector<string> localAddr;
    Utils::tokenize(opt->getValue("start-at"), ":", localAddr);
    ip = localAddr[0];
    port = localAddr[1];
    dataDirPath = opt->getValue("data-dir-path");

    vector<string> seedsAddrs;
    Utils::tokenize(opt->getValue("seeds"), ",", seedsAddrs);
    for (string sa : seedsAddrs) {
        vector<string> addr;
        pair<string, string> p;
        Utils::tokenize(sa, ":", addr);
        p.first = addr[0];
        p.second = addr[1];
        seeds.push_back(p);
    }

    logger->info("Node be reachable at : {}", opt->getValue("start-at"));
    logger->info("Cluster seeds at        : {}", opt->getValue("seeds"));
}
