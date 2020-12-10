#include "handlers/addLinkHandler.hpp"

AddLinkHandler::AddLinkHandler(std::shared_ptr<LinkRequest> request, std::shared_ptr<Response> response)
  : request_(request), response_(response)
{
}

void AddLinkHandler::execute() {
  return;
}
