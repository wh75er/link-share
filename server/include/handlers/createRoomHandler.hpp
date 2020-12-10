#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

class CreateRoomHandler: public BaseHandler {
public:
  CreateRoomHandler(RoomRequest &request, Response &response);
  ~CreateRoomHandler() {};

  void execute() override;

private:
  RoomRequest& request_;
  Response& response_;
};
