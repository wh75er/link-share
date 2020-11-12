#pragma once

#include <string.h>
#include <memory>

#define BOOST_ASIO_HAS_MOVE 1

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "requestHandler.hpp"

class Connection : public std::enable_shared_from_this<Connection> {
public:
  explicit Connection(boost::asio::ip::tcp::socket socket);
  ~Connection();

  std::string read();
  void write(std::string data);

private:
  boost::asio::ip::tcp::socket socket_;
  std::unique_ptr<RequestHandler> rh;
};
