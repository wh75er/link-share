#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"

class DeleteUserFromRoomHandler: public BaseHandler {
public:
  DeleteUserFromRoomHandler(Room &request, Response &response);
  ~DeleteUserFromRoomHandler() override {}

  void execute() override;

private:
  Room& request_;
  Response& response_;
};
