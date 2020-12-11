#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

class DeleteLinkHandler: public BaseHandler {
public:
  DeleteLinkHandler(LinkRequest request);
  ~DeleteLinkHandler() {};

  void execute() override;

private:
  LinkRequest request_;
};
