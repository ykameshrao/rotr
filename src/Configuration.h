//
// Created by kamesh on 30/6/19.
//

#ifndef ROTR_CONFIGURATION_H
#define ROTR_CONFIGURATION_H

#include <iostream>
#include <vector>
#include <algorithm>

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
        string logDirPath;
        uint16_t tick;
        vector <node> nodes;
    };

    class Configuration {
    private:
        string _configPath;
        string _nodeId;
        cluster _clusterConfig;

    public:
        Configuration(int argc, char* argv[]);
        Configuration(const Configuration &) = delete;
        Configuration &operator=(const Configuration &) = delete;
        Configuration(Configuration &&) = delete;
        Configuration &operator=(Configuration &&) = delete;

        string configPath() { return _configPath; }
        string nodeId() { return _nodeId; }
        cluster clusterConfig() { return _clusterConfig; }
    };
}


#endif //ROTR_CONFIGURATION_H
