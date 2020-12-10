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
  AddLinkHandler(std::shared_ptr<LinkRequest> request, std::shared_ptr<Response> response);
  ~AddLinkHandler() {};

  void execute() override;

private:
  std::shared_ptr<LinkRequest> request_;
  std::shared_ptr<Response> response_;
};
