#include "requestHandler.hpp"

#include "connection.hpp"

RequestHandler::RequestHandler(std::shared_ptr<Connection> connection)
  : sender(connection)
{
}

void RequestHandler::handle(std::string data) {
  // Create parser & parse data
  
  // Create handle for corresponding command
  
  // execute handle

  // use sender to send data back to client

  return;
}
