#include "requestHandler.hpp"

#include "connection.hpp"

#include <unistd.h>

RequestHandler::RequestHandler(std::shared_ptr<Connection> connection)
  : sender(std::move(connection))
{
#ifdef DEBUG
  std::cout <<  "RequestHandler constructor" << std::endl;
  unsigned int microseconds = 3 * 1e+6;
  usleep(microseconds);
#endif
}

void RequestHandler::handle(std::string data) {
#ifdef DEBUG
  std::cout << "Data inside of request handler is: " << data << std::endl;
#endif

  // Create parser & parse data
  parser = std::make_shared<TcpStringBodyParser>();

//  handler = parser->parse(data);

  // set response on handler

  // execute handler

  // use sender to send data back to client

  sender.send(data);

  return;
}
