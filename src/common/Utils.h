//
// Created by ykameshrao on 7/6/19.
//

#ifndef ROTR_UTILS_H
#define ROTR_UTILS_H

#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

namespace rotr::common {
    class Utils {
    public:
        static void tokenize(const string &str, const string &delim, vector<std::string> &out);
    };

    void Utils::tokenize(const string &str, const string &delim, vector<string> &out) {
        char *token = strtok(const_cast<char*>(str.c_str()), delim.c_str());
        while (token != nullptr) {
            out.push_back(std::string(token));
            token = strtok(nullptr, delim.c_str());
        }
    }
}


#endif //ROTR_UTILS_H
