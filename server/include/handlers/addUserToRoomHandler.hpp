#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "user.hpp"
#include "response.hpp"

class AddUserToRoomHandler: BaseHandler {
public:
  AddUserToRoomHandler(User &request, Response &response);
  ~AddUserToRoomHandler() override {}

  void execute() override;

private:
  User request_;
  Response response_;
};
