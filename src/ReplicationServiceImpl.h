//
// Created by ykameshrao on 1/7/19.
//

#ifndef ROTR_REPLICATIONSERVICEIMPL_H
#define ROTR_REPLICATIONSERVICEIMPL_H

#include <iostream>
#include <grpc++/grpc++.h>
#include "proto/generated/rotr.pb.h"
#include "proto/generated/rotr.grpc.pb.h"
#include "ClusterHandler.h"

namespace rotr {
    class ReplicationServiceImpl final : public rotr::ReplicationService::Service {
        unique_ptr<ClusterHandler> _clusterHandler;
    public:
        ReplicationServiceImpl(unique_ptr<ClusterHandler> handler) : _clusterHandler{move(handler)} {}

        grpc::Status AppendEntries(::grpc::ServerContext *context, const ::rotr::AppendEntriesRequest *request,
                                  ::rotr::AppendEntriesResponse *response) override;
    };
}

#endif //ROTR_REPLICATIONSERVICEIMPL_H
