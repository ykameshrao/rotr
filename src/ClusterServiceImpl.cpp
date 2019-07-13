//
// Created by ykameshrao on 1/7/19.
//

#include "ClusterServiceImpl.h"

grpc::Status rotr::ClusterServiceImpl::RegisterNode(::grpc::ServerContext *context,
                                                                const ::rotr::BrokerInfo *request,
                                                                ::rotr::ClusterInfo *response) {
    return Service::RegisterNode(context, request, response);
}

grpc::Status rotr::ClusterServiceImpl::DiscoverClusterById(::grpc::ServerContext *context,
                                                                       const ::google::protobuf::StringValue *request,
                                                                       ::rotr::ClusterInfo *response) {
    return Service::DiscoverClusterById(context, request, response);
}
