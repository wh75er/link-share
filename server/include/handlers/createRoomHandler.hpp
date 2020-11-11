#pragma once

#include <string>

#include "handlers/baseHandler.hpp"

class CreateRoomHandler: BaseHandler {
public:
  CreateRoomHandler(Room &request, Response &response);
  ~CreateRoomHandler() override;

  void execute() override;

private:
  Room request_;
  Response response_;
};
