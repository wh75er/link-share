#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

class DeleteRoomHandler: public BaseHandler {
public:
  DeleteRoomHandler(RoomRequest request);
  ~DeleteRoomHandler() {};

  void execute() override;

private:
  RoomRequest request_;
};
