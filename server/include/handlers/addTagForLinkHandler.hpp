#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"

class AddTagForLinkHandler: public BaseHandler {
public:
  AddTagForLinkHandler(WebLink &request, Response &response);
  ~AddTagForLinkHandler() {};

  void execute() override;

private:
  WebLink& request_;
  Response& response_;
};
