#include "requestHandler.hpp"

#include "connection.hpp"

#include <unistd.h>

RequestHandler::RequestHandler(std::shared_ptr<Connection> connection)
  : sender(std::move(connection))
{
  std::cout <<  "RequestHandler constructor" << std::endl;
  unsigned int microseconds = 3 * 1e+6;
  usleep(microseconds);
}

void RequestHandler::handle(std::string data) {
  std::cout << "Data inside of request handler is: " << data << std::endl;

  // Create parser & parse data
  parser = std::make_shared<TcpStringBodyParser>();

  int command = 0;
  std::shared_ptr<BaseRequest> request;
  std::tie(command, request) = parser->parse(data);

  // Produce command for corresponding command id

  // execute command

  // use sender to send data back to client

  return;
}
