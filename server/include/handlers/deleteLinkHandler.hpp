#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

class DeleteLinkHandler: public BaseHandler {
public:
  DeleteLinkHandler(std::shared_ptr<LinkRequest> request, std::shared_ptr<Response> response);
  ~DeleteLinkHandler() {};

  void execute() override;

private:
  std::shared_ptr<LinkRequest> request_;
  std::shared_ptr<Response> response_;
};
