#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"

class AddLinkHandler: public BaseHandler {
public:
  AddLinkHandler();
  AddLinkHandler(WebLink &request, Response &response);
  ~AddLinkHandler() {};

  void execute() override;

private:
  WebLink& request_;
  Response& response_;
};
