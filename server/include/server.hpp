#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <memory>

#include "connection.hpp"

using namespace boost::asio;

class TCPserver {
public:
  TCPserver(std::string address, int port);
  ~TCPserver();

  void accept(std::shared_ptr<Connection> connection);
  void listen();

private:
  io_context ioc_;
  ip::tcp::socket acceptor_;
  std::string address_;
  int port_;
};
