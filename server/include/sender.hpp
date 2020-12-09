#pragma once

#include <iostream>

#include <string>
#include <memory>

class Connection;

class Sender {
public:
  explicit Sender(std::shared_ptr<Connection> connection);
  ~Sender() {std::cout << "Sender destructor" << std::endl;};

  void send(std::string data);

private:
  std::shared_ptr<Connection> connection_;
};
