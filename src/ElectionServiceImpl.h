//
// Created by Kamesh Rao Yeduvakula on 30/4/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//
#ifndef ROTR_ELECTIONSERVICEIMPL_H
#define ROTR_ELECTIONSERVICEIMPL_H

#include <grpcpp/grpcpp.h>

#include "proto/generated/rotr.pb.h"
#include "proto/generated/rotr.grpc.pb.h"

namespace rotr {
    class ElectionServiceImpl final : public ElectionService::Service {
        ::grpc::Status RequestVote(::grpc::ServerContext* context,
                const ::rotr::RequestVoteRequest* request, ::rotr::RequestVoteResponse* response);
    };
}

#endif //ROTR_ELECTIONSERVICEIMPL_H
