#include "handlers/logInUserHandler.hpp"

LogInUserHandler::LogInUserHandler(User &request, Respnse &response)
  : request_(request), response_(response)
{
}

void LogInUserHandler::execute() {
  return;
}
