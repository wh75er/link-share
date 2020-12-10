#include "handlers/addUserToRoomHandler.hpp"

AddUserToRoomHandler::AddUserToRoomHandler(std::shared_ptr<RoomRequest> request, std::shared_ptr<Response> response)
  : request_(request), response_(response)
{
}

void AddUserToRoomHandler::execute() {
  return;
}
