#pragma once

#include <iostream>

#include <string.h>
#include <memory>

#include "requestHandler.hpp"
#include "socket.hpp"

template<class DbOps, class Uuid, class JsonParser>
class Connection : public std::enable_shared_from_this<Connection<DbOps, Uuid, JsonParser>> {
public:
  explicit Connection(std::shared_ptr<BaseTcpSocket> socket);
  ~Connection() {
#ifdef DEBUG
    std::cout << "Connection destructor" << std::endl;
#endif
  };

  std::string read();
  void write(const std::string& str);
  void start(std::shared_ptr<DbOps> dbops);
  void finish();

private:
  std::shared_ptr<BaseTcpSocket> socket_;
  std::unique_ptr<RequestHandler<DbOps, Connection<DbOps, Uuid, JsonParser>, Uuid, JsonParser>> rh;
};

#include "connection.tpp"