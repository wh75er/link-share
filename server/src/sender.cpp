#include "sender.hpp"

#include "connection.hpp"

Sender::Sender(std::shared_ptr<Connection> cnct)
  : cnct_(cnct)
{
}

void Sender::send(std::string data) {
  return;
}
