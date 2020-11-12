#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"

class AddUserToRoomHandler: public BaseHandler {
public:
  AddUserToRoomHandler(Room &request, Response &response);
  ~AddUserToRoomHandler() override {}

  void execute() override;

private:
  Room& request_;
  Response& response_;
};
