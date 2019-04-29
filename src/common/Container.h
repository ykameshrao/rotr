//
// Created by Kamesh Rao Yeduvakula on 31/3/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//
#ifndef ROTR_CONTAINER_H
#define ROTR_CONTAINER_H

#include <iostream>
#include <memory>

#include "Logger.h"

namespace rotr::common {
    class Container {
        Container() = default;

        Container(const Container &) = delete;

        Container &operator=(const Container &) = delete;

        Container(Container &&) = delete;

        Container &operator=(Container &&) = delete;

        ~Container();

    public:
        std::shared_ptr<Logger> logger;

        static Container &I() {
            static Container C;
            return C;
        }
    };
}


#endif //ROTR_CONTAINER_H
