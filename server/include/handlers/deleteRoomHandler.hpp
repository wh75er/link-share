#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"

class DeleteRoomHandler: public BaseHandler {
public:
  DeleteRoomHandler(Room &request, Response &response);
  ~DeleteRoomHandler() override {}

  void execute() override;

private:
  Room& request_;
  Response& response_;
};
