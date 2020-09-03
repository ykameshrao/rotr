//
// Created by kamesh on 30/6/19.
//

#ifndef ROTR_CONFIGURATION_H
#define ROTR_CONFIGURATION_H

#include "yaml-cpp/yaml.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

namespace rotr {
    struct node {
        string id;
        string host;
        uint16_t rotrPort;
        uint16_t replicationPort;
        uint16_t electionPort;
    };

    struct cluster {
        string clusterId;
        string clusterName;
        string dataDirPath;
        uint16_t tick;
        unordered_map <string, node> nodes;
    };

    class Configuration {
    private:
        string _configFilePath;
        string _nodeId;
        cluster _clusterConfig;

    public:
        Configuration(int argc, char* argv[]);
        Configuration(const Configuration &) = delete;
        Configuration &operator=(const Configuration &) = delete;
        Configuration(Configuration &&) = delete;
        Configuration &operator=(Configuration &&) = delete;

        string configPath() { return _configFilePath; }
        string nodeId() { return _nodeId; }
        cluster clusterConfig() { return _clusterConfig; }
        node curNodeConfig() { return _clusterConfig.nodes[nodeId()]; }
        void parseAndLoadConfig(string configFilePath);
    };
}


#endif //ROTR_CONFIGURATION_H
