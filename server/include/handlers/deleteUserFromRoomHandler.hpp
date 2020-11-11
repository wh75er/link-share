#pragma once

#include <string>

#include "handlers/baseHandler.hpp"

class DeleteUserFromRoomHandler: BaseHandler {
public:
  DeleteUserFromRoomHandler(User &request, Response &response);
  ~DeleteUserFromRoomHandler() override;

  void execute() override;

private:
  User request_;
  Response response_;
};
