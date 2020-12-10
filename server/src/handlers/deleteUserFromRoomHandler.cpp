#include "handlers/deleteUserFromRoomHandler.hpp"

DeleteUserFromRoomHandler::DeleteUserFromRoomHandler(std::shared_ptr<UsersRoomRequest> request, std::shared_ptr<Response> response)
  : request_(request), response_(response)
{
}

void DeleteUserFromRoomHandler::execute() {
  return;
}
