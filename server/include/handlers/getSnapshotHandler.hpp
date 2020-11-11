#pragma once

#include <string>

#include "handlers/baseHandler.hpp"

class GetSnapshotHandler: BaseHandler {
public:
  GetSnapshotHandler(WebLink &request, Response &response);
  ~GetSnapshotHandler() override;

  void execute() override;

private:
  WebLink request_;
  Response response_;
};
