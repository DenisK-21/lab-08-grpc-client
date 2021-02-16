#include <iostream>
#include <iomanip>
#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "echo.grpc.pb.h"
#include "echo.pb.h"

using grpc::ClientContext;
using grpc::Status;
using suggest::SuggestRequest;
using suggest::SuggestAnswer;
using suggest::SuggestResponse;
using suggest::Suggest;

int main(int argc, char** argv) {

  auto channel = grpc::CreateChannel("0.0.0.0:9090", grpc::InsecureChannelCredentials());
  auto client = suggestService::NewStub(channel);
  SuggestResponse response;
  ClientContext context;
  SuggestRequest request;
  request.set_data(argv[1]);
  Status status = client->Query(&context, request, &response);

  if (status.ok()) {

    std::cout << response.data() << std::endl;
  } else {
    return -1;
  }
}
