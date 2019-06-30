//
// Created by kamesh on 30/6/19.
//

#ifndef ROTR_CONFIGURATION_H
#define ROTR_CONFIGURATION_H

#include <iostream>
#include <vector>

using namespace std;

namespace rotr {
    class Configuration {
    public:
        Configuration(int argc, char* argv[]);
        Configuration(const Configuration &) = delete;
        Configuration &operator=(const Configuration &) = delete;
        Configuration(Configuration &&) = delete;
        Configuration &operator=(Configuration &&) = delete;

        string dataDirPath;
        string port;
        string ip;
        vector<pair<string, string>> seeds;
    };
}


#endif //ROTR_CONFIGURATION_H
