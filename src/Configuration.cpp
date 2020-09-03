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
    opt->addUsage("--config-path \t\tUser defined yaml based configuration for the cluster");

    opt->setOption("node-id");
    opt->setOption("config-path");

    opt->processCommandArgs(argc, argv);

    if (!opt->hasOptions()) { /* print usage if no options */
        opt->printUsage();
        exit(-1);
    }

    _nodeId = opt->getValue("node-id");
    _configFilePath = opt->getValue("config-path");

    parseAndLoadConfig(_configFilePath);

    logger->info("Rotr Service be reachable at: {}", clusterConfig().nodes.front().rotrPort);
    logger->info("Rotr data dir at: {}", clusterConfig().dataDirPath);
    logger->info("ClusterId: {}", clusterConfig().clusterId);
    logger->info("NodeId: {}", nodeId());
}

void rotr::Configuration::parseAndLoadConfig(string configFilePath) {
    YAML::Node config = YAML::LoadFile(configFilePath);
    _clusterConfig.clusterId = config["clusterId"].as<string>();
    _clusterConfig.clusterName = config["clusterName"].as<string>();
    _clusterConfig.dataDirPath = config["dataDir"].as<string>();
    _clusterConfig.logDirPath = config["logDir"].as<string>();
    _clusterConfig.tick = config["tick"].as<uint16_t>();

    YAML::Node rotrNodes = config["nodes"];
    for (size_t i = 0; i < rotrNodes.size(); i++) {
        node rotrNode;
        rotrNode.id = rotrNodes[i]["id"].as<string>();
        rotrNode.host = rotrNodes[i]["host"].as<string>();
        rotrNode.rotrPort = rotrNodes[i]["rotrPort"].as<uint16_t>();
        rotrNode.replicationPort = rotrNodes[i]["replicationPort"].as<uint16_t>();
        rotrNode.electionPort = rotrNodes[i]["electionPort"].as<uint16_t>();
        _clusterConfig.nodes.push_back(move(rotrNode));
    }
}
