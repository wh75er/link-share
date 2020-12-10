#pragma once

#include <iostream>

#include <string>
#include <memory>

#include "bodyParser.hpp"
#include "sender.hpp"
#include "handlers/baseHandler.hpp"

class Connection;

class RequestHandler {
public:
  explicit RequestHandler(std::shared_ptr<Connection> connection);
  ~RequestHandler() { std::cout << "RequestHandler destructor" << std::endl;};

  void handle(std::string data);

private:
  std::shared_ptr<AbstractBodyParser> parser;
  BaseHandler handler;
  Sender sender;
};
