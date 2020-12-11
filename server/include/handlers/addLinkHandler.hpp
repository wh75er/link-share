#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

class AddLinkHandler: public BaseHandler {
public:
  AddLinkHandler();
  AddLinkHandler(LinkRequest request);
  ~AddLinkHandler() {};

  void execute() override;

private:
  LinkRequest request_;
};
