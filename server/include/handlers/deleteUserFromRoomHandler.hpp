#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

class DeleteUserFromRoomHandler: public BaseHandler {
public:
  DeleteUserFromRoomHandler(UsersRoomRequest &request, Response &response);
  ~DeleteUserFromRoomHandler() {};

  void execute() override;

private:
  UsersRoomRequest& request_;
  Response& response_;
};
