#pragma once

#include <string>

#include "handlers/baseHandler.hpp"

class AddLinkHandler: BaseHandler {
public:
  AddLinkHandler(WebLink &request, Response &response);
  ~AddLinkHandler() override;

  void execute() override;

private:
  WebLink request_;
  Response response_;
};
