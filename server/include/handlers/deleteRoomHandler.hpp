#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

class DeleteRoomHandler: public BaseHandler {
public:
  DeleteRoomHandler(std::shared_ptr<RoomRequest> request, std::shared_ptr<Response> response);
  ~DeleteRoomHandler() {};

  void execute() override;

private:
  std::shared_ptr<RoomRequest> request_;
  std::shared_ptr<Response> response_;
};
