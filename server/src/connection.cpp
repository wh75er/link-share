#include "connection.hpp"

Connection::Connection(const BaseTcpSocket& socket): 
  socket_(std::move(socket)),
  rh(nullptr)
{
  std::cout << "Connection constructor\n" << std::endl;
}

std::string Connection::read() {
  return "";
}

void Connection::write(std::string data) {
  return;
}
