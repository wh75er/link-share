#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string.h>

class Connection {
public:
  explicit Connection(boost::asio::ip::tcp::socket socket);
  ~Connection();

  std::string read();
  void write(std::string data);

private:
  boost::asio::ip::tcp::socket socket_;
  RequestManager rm;
};
