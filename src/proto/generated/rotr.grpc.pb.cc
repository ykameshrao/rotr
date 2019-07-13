// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: rotr.proto

#include "rotr.pb.h"
#include "rotr.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace rotr {

static const char* RaftInternalRPC_method_names[] = {
  "/rotr.RaftInternalRPC/AppendEntries",
  "/rotr.RaftInternalRPC/RequestVote",
};

std::unique_ptr< RaftInternalRPC::Stub> RaftInternalRPC::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< RaftInternalRPC::Stub> stub(new RaftInternalRPC::Stub(channel));
  return stub;
}

RaftInternalRPC::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_AppendEntries_(RaftInternalRPC_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RequestVote_(RaftInternalRPC_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status RaftInternalRPC::Stub::AppendEntries(::grpc::ClientContext* context, const ::rotr::AppendEntriesRequest& request, ::rotr::AppendEntriesResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AppendEntries_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::rotr::AppendEntriesResponse>* RaftInternalRPC::Stub::AsyncAppendEntriesRaw(::grpc::ClientContext* context, const ::rotr::AppendEntriesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::rotr::AppendEntriesResponse>::Create(channel_.get(), cq, rpcmethod_AppendEntries_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::rotr::AppendEntriesResponse>* RaftInternalRPC::Stub::PrepareAsyncAppendEntriesRaw(::grpc::ClientContext* context, const ::rotr::AppendEntriesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::rotr::AppendEntriesResponse>::Create(channel_.get(), cq, rpcmethod_AppendEntries_, context, request, false);
}

::grpc::Status RaftInternalRPC::Stub::RequestVote(::grpc::ClientContext* context, const ::rotr::RequestVoteRequest& request, ::rotr::RequestVoteResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_RequestVote_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::rotr::RequestVoteResponse>* RaftInternalRPC::Stub::AsyncRequestVoteRaw(::grpc::ClientContext* context, const ::rotr::RequestVoteRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::rotr::RequestVoteResponse>::Create(channel_.get(), cq, rpcmethod_RequestVote_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::rotr::RequestVoteResponse>* RaftInternalRPC::Stub::PrepareAsyncRequestVoteRaw(::grpc::ClientContext* context, const ::rotr::RequestVoteRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::rotr::RequestVoteResponse>::Create(channel_.get(), cq, rpcmethod_RequestVote_, context, request, false);
}

RaftInternalRPC::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      RaftInternalRPC_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< RaftInternalRPC::Service, ::rotr::AppendEntriesRequest, ::rotr::AppendEntriesResponse>(
          std::mem_fn(&RaftInternalRPC::Service::AppendEntries), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      RaftInternalRPC_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< RaftInternalRPC::Service, ::rotr::RequestVoteRequest, ::rotr::RequestVoteResponse>(
          std::mem_fn(&RaftInternalRPC::Service::RequestVote), this)));
}

RaftInternalRPC::Service::~Service() {
}

::grpc::Status RaftInternalRPC::Service::AppendEntries(::grpc::ServerContext* context, const ::rotr::AppendEntriesRequest* request, ::rotr::AppendEntriesResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status RaftInternalRPC::Service::RequestVote(::grpc::ServerContext* context, const ::rotr::RequestVoteRequest* request, ::rotr::RequestVoteResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* ClusterService_method_names[] = {
  "/rotr.ClusterService/RegisterNode",
  "/rotr.ClusterService/DiscoverClusterById",
};

std::unique_ptr< ClusterService::Stub> ClusterService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ClusterService::Stub> stub(new ClusterService::Stub(channel));
  return stub;
}

ClusterService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_RegisterNode_(ClusterService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DiscoverClusterById_(ClusterService_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ClusterService::Stub::RegisterNode(::grpc::ClientContext* context, const ::rotr::NodeInfo& request, ::rotr::ClusterInfo* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_RegisterNode_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::rotr::ClusterInfo>* ClusterService::Stub::AsyncRegisterNodeRaw(::grpc::ClientContext* context, const ::rotr::NodeInfo& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::rotr::ClusterInfo>::Create(channel_.get(), cq, rpcmethod_RegisterNode_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::rotr::ClusterInfo>* ClusterService::Stub::PrepareAsyncRegisterNodeRaw(::grpc::ClientContext* context, const ::rotr::NodeInfo& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::rotr::ClusterInfo>::Create(channel_.get(), cq, rpcmethod_RegisterNode_, context, request, false);
}

::grpc::Status ClusterService::Stub::DiscoverClusterById(::grpc::ClientContext* context, const ::google::protobuf::StringValue& request, ::rotr::ClusterInfo* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_DiscoverClusterById_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::rotr::ClusterInfo>* ClusterService::Stub::AsyncDiscoverClusterByIdRaw(::grpc::ClientContext* context, const ::google::protobuf::StringValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::rotr::ClusterInfo>::Create(channel_.get(), cq, rpcmethod_DiscoverClusterById_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::rotr::ClusterInfo>* ClusterService::Stub::PrepareAsyncDiscoverClusterByIdRaw(::grpc::ClientContext* context, const ::google::protobuf::StringValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::rotr::ClusterInfo>::Create(channel_.get(), cq, rpcmethod_DiscoverClusterById_, context, request, false);
}

ClusterService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ClusterService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ClusterService::Service, ::rotr::NodeInfo, ::rotr::ClusterInfo>(
          std::mem_fn(&ClusterService::Service::RegisterNode), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ClusterService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ClusterService::Service, ::google::protobuf::StringValue, ::rotr::ClusterInfo>(
          std::mem_fn(&ClusterService::Service::DiscoverClusterById), this)));
}

ClusterService::Service::~Service() {
}

::grpc::Status ClusterService::Service::RegisterNode(::grpc::ServerContext* context, const ::rotr::NodeInfo* request, ::rotr::ClusterInfo* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ClusterService::Service::DiscoverClusterById(::grpc::ServerContext* context, const ::google::protobuf::StringValue* request, ::rotr::ClusterInfo* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace rotr

