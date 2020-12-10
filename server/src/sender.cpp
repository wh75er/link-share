#include "sender.hpp"

#include "connection.hpp"

Sender::Sender(std::shared_ptr<Connection> connection)
  : connection_(connection)
{
#ifdef DEBUG
  std::cout << "Sender constructor" << std::endl;
#endif
}

void Sender::send(std::string data) {
    connection_->write(data);
    connection_->finish();
    connection_.reset();
}
