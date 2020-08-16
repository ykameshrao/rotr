//
// Created by Kamesh Rao Yeduvakula on 30/4/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//
#include "ElectionServiceImpl.h"

::grpc::Status
rotr::ElectionServiceImpl::RequestVote(::grpc::ServerContext *context, const ::rotr::RequestVoteRequest *request,
                                       ::rotr::RequestVoteResponse *response) {
    return Service::RequestVote(context, request, response);
}
