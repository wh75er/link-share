#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

class GetSnapshotHandler: public BaseHandler {
public:
  GetSnapshotHandler(SnapshotRequest &request, Response &response);
  ~GetSnapshotHandler() {};

  void execute() override;

private:
  SnapshotRequest& request_;
  Response& response_;
};
