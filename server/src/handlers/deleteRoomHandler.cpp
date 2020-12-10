#include "handlers/deleteRoomHandler.hpp"

DeleteRoomHandler::DeleteRoomHandler(std::shared_ptr<RoomRequest> request, std::shared_ptr<Response> response)
  : request_(request), response_(response)
{
}

void DeleteRoomHandler::execute() {
  return;
}
