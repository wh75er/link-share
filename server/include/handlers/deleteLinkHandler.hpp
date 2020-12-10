#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

class DeleteLinkHandler: public BaseHandler {
public:
  DeleteLinkHandler(LinkRequest &request, Response &response);
  ~DeleteLinkHandler() {};

  void execute() override;

private:
  LinkRequest& request_;
  Response& response_;
};
