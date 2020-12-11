#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

class CreateRoomHandler: public BaseHandler {
public:
  CreateRoomHandler(RoomRequest request);
  ~CreateRoomHandler() {};

  void execute() override;

private:
  RoomRequest request_;
};
