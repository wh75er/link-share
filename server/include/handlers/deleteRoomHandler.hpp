#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

class DeleteRoomHandler: public BaseHandler {
public:
  DeleteRoomHandler(RoomRequest &request, Response &response);
  ~DeleteRoomHandler() {};

  void execute() override;

private:
  RoomRequest& request_;
  Response& response_;
};
