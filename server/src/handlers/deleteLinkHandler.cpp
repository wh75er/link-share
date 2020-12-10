#include "handlers/deleteLinkHandler.hpp"

DeleteLinkHandler::DeleteLinkHandler(std::shared_ptr<LinkRequest> request, std::shared_ptr<Response> response)
  : request_(request), response_(response)
{
}

void DeleteLinkHandler::execute() {
  return;
}
