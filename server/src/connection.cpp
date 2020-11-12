#include "connection.hpp"

Connection::Connection(boost::asio::ip::tcp::socket socket)
  : socket_(std::move(socket)), 
    rh(nullptr)
{
}

std::string Connection::read() {
  return "";
}

void Connection::write(std::string data) {
  return;
}
