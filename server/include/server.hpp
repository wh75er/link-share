#pragma once

#include <string>
#include <memory>

#include "connection.hpp"
#include "socket.hpp"

class TCPserver {
public:
  TCPserver(std::string address, std::string port);
  ~TCPserver();

  void accept(std::shared_ptr<Connection> connection);
  void listen();

private:
  BaseTcpSocket socket_;
  std::string address_;
  std::string port_;
};
