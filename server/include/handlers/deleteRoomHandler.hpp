#pragma once

#include <string>

#include "handlers/baseHandler.hpp"

class DeleteRoomHandler: BaseHandler {
public:
  DeleteRoomHandler(Room &request, Response &response);
  ~DeleteRoomHandler() override;

  void execute() override;

private:
  Room request_;
  Response response_;
};
