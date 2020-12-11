#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

class GetSnapshotHandler: public BaseHandler {
public:
  GetSnapshotHandler(SnapshotRequest request);
  ~GetSnapshotHandler() {};

  void execute() override;

private:
  SnapshotRequest request_;
};
