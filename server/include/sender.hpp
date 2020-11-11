#pragma once

#include <string>
#include <memory>

class Sender {
public:
  Sender(std::shared_ptr<Connection>, cnct);
  ~Sender();

  void send(std::string body);
private:
  Connection cnct;
};
