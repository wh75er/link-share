#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"

class DeleteLinkHandler: public BaseHandler {
public:
  DeleteLinkHandler(WebLink &request, Response &response);
  ~DeleteLinkHandler() override {}

  void execute() override;

private:
  WebLink& request_;
  Response& response_;
};
