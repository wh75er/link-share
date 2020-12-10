#pragma once

#include <string>
#include <memory>

#include "handlers/baseHandler.hpp"
#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

class DeleteUserFromRoomHandler: public BaseHandler {
public:
  DeleteUserFromRoomHandler(std::shared_ptr<UsersRoomRequest> request, std::shared_ptr<Response> response);
  ~DeleteUserFromRoomHandler() {};

  void execute() override;

private:
  std::shared_ptr<UsersRoomRequest> request_;
  std::shared_ptr<Response> response_;
};
