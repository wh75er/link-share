#pragma once

#include <iostream>

#include <string>
#include <memory>

#include "connection.hpp"
#include "response.hpp"

template<class Connection>
class Sender {
public:
  explicit Sender(std::shared_ptr<Connection> connection);
  ~Sender() {
#ifdef DEBUG
    std::cout << "Sender destructor" << std::endl;
#endif
  };

  void send(std::shared_ptr<Response> response);

private:
  std::vector<std::string> form_packages(std::string data, char status);

  std::shared_ptr<Connection> connection_;
};

#include "sender.tpp"