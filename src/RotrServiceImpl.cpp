//
// Created by ykameshrao on 13/08/20.
//

#include "RotrServiceImpl.h"

::grpc::Status rotr::RotrServiceImpl::Get(::grpc::ServerContext *context, const ::rotr::RotrGetRequest *request,
                                          ::rotr::RotrGetResponse *response) {
    return Service::Get(context, request, response);
}

::grpc::Status rotr::RotrServiceImpl::Put(::grpc::ServerContext *context, const ::rotr::RotrPutRequest *request,
                                          ::rotr::RotrPutResponse *response) {
    return Service::Put(context, request, response);
}

::grpc::Status rotr::RotrServiceImpl::DiscoverCluster(::grpc::ServerContext *context, const ::rotr::Null *request,
                                                      ::rotr::ClusterInfo *response) {
    return Service::DiscoverCluster(context, request, response);
}
