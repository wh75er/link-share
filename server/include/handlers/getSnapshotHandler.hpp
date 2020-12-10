#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

class GetSnapshotHandler: public BaseHandler {
public:
  GetSnapshotHandler(std::shared_ptr<SnapshotRequest> request, std::shared_ptr<Response> response);
  ~GetSnapshotHandler() {};

  void execute() override;

private:
  std::shared_ptr<SnapshotRequest> request_;
  std::shared_ptr<Response> response_;
};
