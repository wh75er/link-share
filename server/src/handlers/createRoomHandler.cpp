#include "handlers/createRoomHandler.hpp"

CreateRoomHandler::CreateRoomHandler(std::shared_ptr<RoomRequest> request, std::shared_ptr<Response> response)
  : request_(request), response_(response)
{
}

void CreateRoomHandler::execute() {
  return;
}
