#include "connection.hpp"

Connection::Connection(const BaseTcpSocket& socket): 
  socket_(std::move(socket))
{
  std::cout << "Connection constructor" << std::endl;
}

std::string Connection::read() {
  return "";
}

void Connection::write(std::string data) {
  return;
}

void Connection::start() {
  rh = std::make_unique<RequestHandler>(shared_from_this());
}
