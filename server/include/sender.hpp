#pragma once

#include <iostream>

#include <string>
#include <memory>

class Connection;

class Sender {
public:
  explicit Sender(std::shared_ptr<Connection> connection);
  ~Sender() {
#ifdef DEBUG
    std::cout << "Sender destructor" << std::endl;
#endif
  };

  void send(std::string data);

private:
  std::shared_ptr<Connection> connection_;
};
