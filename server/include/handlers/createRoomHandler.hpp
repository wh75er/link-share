#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"

class CreateRoomHandler: BaseHandler {
public:
  CreateRoomHandler(Room &request, Response &response);
  ~CreateRoomHandler() override {}

  void execute() override;

private:
  Room& request_;
  Response& response_;
};
