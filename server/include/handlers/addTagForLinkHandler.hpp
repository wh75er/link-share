#pragma once

#include <string>

#include "handlers/baseHandler.hpp"

class AddTagForLinkHandler: BaseHandler {
public:
  AddTagForLinkHandler(Tag &request, Response &response);
  ~AddTagForLinkHandler() override;

  void execute() override;

private:
  Tag request_;
  Response response_;
};
