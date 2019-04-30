//
// Created by Kamesh Rao Yeduvakula on 30/4/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//
#ifndef ROTR_RAFTINTERNALRPCSERVICEIMPL_H
#define ROTR_RAFTINTERNALRPCSERVICEIMPL_H

#include <grpcpp/grpcpp.h>

#include "proto/generated/rotr.pb.h"
#include "proto/generated/rotr.grpc.pb.h"

namespace rotr {
    class RaftInternalRPCServiceImpl final : public RaftInternalRPC::Service {
        ::grpc::Status AppendEntries(::grpc::ServerContext* context,
                const ::rotr::AppendEntriesRequest* request, ::rotr::AppendEntriesResponse* response);

        ::grpc::Status RequestVote(::grpc::ServerContext* context,
                const ::rotr::RequestVoteRequest* request, ::rotr::RequestVoteResponse* response);
    };
}

#endif //ROTR_RAFTINTERNALRPCSERVICEIMPL_H
