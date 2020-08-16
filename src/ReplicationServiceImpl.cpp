//
// Created by ykameshrao on 1/7/19.
//

#include "ReplicationServiceImpl.h"

grpc::Status
rotr::ReplicationServiceImpl::AppendEntries(::grpc::ServerContext *context, const ::rotr::AppendEntriesRequest *request,
                                            ::rotr::AppendEntriesResponse *response) {
    return Service::AppendEntries(context, request, response);
}
