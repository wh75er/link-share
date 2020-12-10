#include "handlers/getSnapshotHandler.hpp"

GetSnapshotHandler::GetSnapshotHandler(SnapshotRequest &request, Response &response)
  : request_(request), response_(response)
{
}

void GetSnapshotHandler::execute() {
  return;
}
