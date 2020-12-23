#pragma once

template<class Connection>
Sender<Connection>::Sender(std::shared_ptr<Connection> connection)
        : connection_(connection)
{
#ifdef DEBUG
  std::cout << "Sender constructor" << std::endl;
#endif
}

template<class Connection>
void Sender<Connection>::send(std::string data) {
#ifdef DEBUG
  std::cout << "Sender data: " << data << std::endl;
#endif
  connection_->write(data);
  connection_->finish();
  connection_.reset();
}
