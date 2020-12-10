#include "handlers/deleteUserFromRoomHandler.hpp"

DeleteUserFromRoomHandler::DeleteUserFromRoomHandler(UsersRoomRequest &request, Response &response)
  : request_(request), response_(response)
{
}

void DeleteUserFromRoomHandler::execute() {
  return;
}
