#include "sender.hpp"

#include "connection.hpp"

Sender::Sender(std::shared_ptr<Connection> connection)
  : connection_(connection)
{
#ifdef DEBUG
  std::cout << "Sender constructor" << std::endl;
#endif
  connection->finish();
  connection_.reset();
}

void Sender::send(std::string data) {
  return;
}
