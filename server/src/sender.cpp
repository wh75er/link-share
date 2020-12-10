#include "sender.hpp"

#include "connection.hpp"

Sender::Sender(std::shared_ptr<Connection> connection)
  : connection_(connection)
{
  std::cout << "Sender constructor" << std::endl;
  connection->finish();
  connection_.reset();
}

void Sender::send(std::string data) {
  return;
}
