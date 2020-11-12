#include "handlers/logInUserHandler.hpp"

LogInUserHandler::LogInUserHandler(User &request, Response &response)
  : request_(request), response_(response)
{
}

void LogInUserHandler::execute() {
  return;
}
