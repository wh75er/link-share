#pragma once

#include <string>
#include <memory>

class RequestHandler {
public:
  explicit RequestHandler(std::shared_ptr<Connection> connection);
  ~RequestHandler();

  void handle(std::string body);

private:
  BodyParser parser;
  Handler handler;
  Sender sender;
};
