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
    class Configuration {
    private:
        string _clusterId;
        string _dataDirPath;
        string _port;
        string _ip;
        vector <pair<string, string>> _seeds;
    public:
        Configuration(int argc, char* argv[]);
        Configuration(const Configuration &) = delete;
        Configuration &operator=(const Configuration &) = delete;
        Configuration(Configuration &&) = delete;
        Configuration &operator=(Configuration &&) = delete;

        string clusterId() { return _clusterId; }
        string ip() { return _ip; }
        string port() { return _port; }
        string dataLocation() { return _dataDirPath; }

        bool isCurrentNodeSeed() {
            return _seeds.end() != find_if(_seeds.begin(), _seeds.end(),
                                           [&](pair <string, string> p) {
                                               return p.first == _ip && p.second == _port;
                                           });
        }
    };
}


#endif //ROTR_CONFIGURATION_H
