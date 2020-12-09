#include "requestHandler.hpp"

#include "connection.hpp"

#include <unistd.h>

RequestHandler::RequestHandler(std::shared_ptr<Connection> connection)
  : sender(connection)
{
  std::cout <<  "RequestHandler constructor" << std::endl;
  unsigned int microseconds = 3 * 1e+6;
  usleep(microseconds);
}

void RequestHandler::handle(std::string data) {
  // Create parser & parse data

  // Produce command for corresponding command id

  // execute command

  // use sender to send data back to client

  return;
}
