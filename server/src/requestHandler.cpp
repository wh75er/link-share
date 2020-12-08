#include "requestHandler.hpp"

#include "connection.hpp"

RequestHandler::RequestHandler(std::shared_ptr<Connection> connection)
  : sender(connection)
{
}

void RequestHandler::handle(std::string data) {
  // Create parser & parse data

  // Produce command for corresponding command id

  // execute command

  // use sender to send data back to client

  return;
}
