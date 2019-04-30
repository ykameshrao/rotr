//
// Created by Kamesh Rao Yeduvakula on 30/4/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//
#include "RaftInternalRPCServiceImpl.h"

::grpc::Status rotr::RaftInternalRPCServiceImpl::AppendEntries(::grpc::ServerContext *context,
                                                               const ::rotr::AppendEntriesRequest *request,
                                                               ::rotr::AppendEntriesResponse *response) {
    return Service::AppendEntries(context, request, response);
}

::grpc::Status
rotr::RaftInternalRPCServiceImpl::RequestVote(::grpc::ServerContext *context, const ::rotr::RequestVoteRequest *request,
                                              ::rotr::RequestVoteResponse *response) {
    return Service::RequestVote(context, request, response);
}
