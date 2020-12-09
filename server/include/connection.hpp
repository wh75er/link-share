#pragma once

#include <iostream>

#include <string.h>
#include <memory>

#include "requestHandler.hpp"
#include "socket.hpp"

class Connection : public std::enable_shared_from_this<Connection> {
public:
  explicit Connection(const BaseTcpSocket& socket);
  ~Connection() {std::cout << "Connection destructor" << std::endl;};

  std::string read();
  void write(std::string data);

private:
  const BaseTcpSocket& socket_;
  std::unique_ptr<RequestHandler> rh;
};
