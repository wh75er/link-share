#include "handlers/getSnapshotHandler.hpp"

GetSnapshotHandler::GetSnapshotHandler(std::shared_ptr<SnapshotRequest> request, std::shared_ptr<Response> response)
  : request_(request), response_(response)
{
}

void GetSnapshotHandler::execute() {
  return;
}
