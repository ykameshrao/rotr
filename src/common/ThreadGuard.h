//
// Created by Kamesh Rao Yeduvakula on 31/3/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//

#ifndef ROTR_THREADGUARD_H
#define ROTR_THREADGUARD_H

#include <iostream>
#include <thread>

using namespace std;

namespace rotr::common {
    class ThreadGuard {
        thread& _t;
    public:
        explicit ThreadGuard(thread& t): _t(t) {}
        ~ThreadGuard() {
            if(_t.joinable()) {
                _t.join();
            }
        }

        ThreadGuard(ThreadGuard const&) = delete;
        ThreadGuard& operator=(ThreadGuard const&) = delete;
    };
}

#endif //ROTR_THREADGUARD_H
