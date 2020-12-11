#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

class AddUserToRoomHandler: public BaseHandler {
public:
  AddUserToRoomHandler(UsersRoomRequest request);
  ~AddUserToRoomHandler() {};

  void execute() override;

private:
  UsersRoomRequest request_;
};
