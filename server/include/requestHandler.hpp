#pragma once

#include <string>
#include <memory>

#include "bodyParser.hpp"
#include "sender.hpp"
#include "handlers/baseHandler.hpp"

class Connection;

class RequestHandler {
public:
  explicit RequestHandler(std::shared_ptr<Connection> connection);
  ~RequestHandler() {}

  void handle(std::string data);

private:
  BodyParser parser;
  BaseHandler handler;
  Sender sender;
};
