//
// Created by ykameshrao on 1/7/19.
//

#ifndef ROTR_CLUSTERSERVICEIMPL_H
#define ROTR_CLUSTERSERVICEIMPL_H

#include <iostream>
#include <grpc++/grpc++.h>
#include "proto/generated/rotr.pb.h"
#include "proto/generated/rotr.grpc.pb.h"
#include "ClusterHandler.h"

namespace rotr {
    class ClusterServiceImpl final : public rotr::ClusterService::Service {
        unique_ptr<ClusterHandler> _clusterHandler;
    public:
        ClusterServiceImpl(unique_ptr<ClusterHandler> handler) : _clusterHandler{move(handler)} {}

        grpc::Status RegisterNode(::grpc::ServerContext *context, const ::rotr::BrokerInfo *request,
                                  ::rotr::ClusterInfo *response) override;

        grpc::Status DiscoverClusterById(::grpc::ServerContext *context, const ::google::protobuf::StringValue *request,
                                         ::rotr::ClusterInfo *response) override;
    };
}

#endif //KNOWHERE_CLUSTERSERVICEIMPL_H
