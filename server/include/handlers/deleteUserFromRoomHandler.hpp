#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

class DeleteUserFromRoomHandler: public BaseHandler {
public:
  DeleteUserFromRoomHandler(UsersRoomRequest request);
  ~DeleteUserFromRoomHandler() {};

  void execute() override;

private:
  UsersRoomRequest request_;
};
