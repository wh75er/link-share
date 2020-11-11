#pragma once

#include <string>

#include "handlers/baseHandler.hpp"

class DeleteLinkHandler: BaseHandler {
public:
  DeleteLinkHandler(WebLink &request, Response &response);
  ~DeleteLinkHandler() override;

  void execute() override;

private:
  WebLink request_;
  Response response_;
};
