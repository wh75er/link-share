#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"

class AddTagForLinkHandler: BaseHandler {
public:
  AddTagForLinkHandler(WebLink &request, Response &response);
  ~AddTagForLinkHandler() override {}

  void execute() override;

private:
  WebLink request_;
  Response response_;
};
