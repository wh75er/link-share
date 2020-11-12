#pragma once

#include <string>
#include <memory>

class Connection;

class Sender {
public:
  explicit Sender(std::shared_ptr<Connection> cnct);
  ~Sender();

  void send(std::string data);

private:
  std::shared_ptr<Connection> cnct_;
};
