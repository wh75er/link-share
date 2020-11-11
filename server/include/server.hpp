#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

class TCPserver {
public:
  TCPserver(std::string address, int port);
  ~TCPserver();

  Connection accept();
  void listen();

private:
  boost::asio::ip::tcp::socket socket;
  std::string addres;
  int port;
};
