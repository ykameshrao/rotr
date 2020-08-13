//
// Created by ykameshrao on 13/08/20.
//

#ifndef ROTR_ROTRSERVICEIMPL_H
#define ROTR_ROTRSERVICEIMPL_H

#include <grpcpp/grpcpp.h>

#include "proto/generated/rotr.pb.h"
#include "proto/generated/rotr.grpc.pb.h"

namespace rotr {
    class RotrServiceImpl final : public RotrService::Service {
        ::grpc::Status Get(::grpc::ServerContext* context,
                                     const ::rotr::RotrGetRequest* request, ::rotr::RotrGetResponse* response);

        ::grpc::Status Put(::grpc::ServerContext* context,
                                   const ::rotr::RotrPutRequest* request, ::rotr::RotrPutResponse* response);

        ::grpc::Status DiscoverCluster(::grpc::ServerContext* context,
                           const ::rotr::Null* request, ::rotr::ClusterInfo* response);
    };
}

#endif //ROTR_ROTRSERVICEIMPL_H
