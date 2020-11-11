#pragma once

#include <string>

#include "handlers/baseHandler.hpp"

class LogInUserHandler: BaseHandler {
public:
  LogInUserHandler(User &request, Response &response);
  ~LogInUserHandler() override;

  void execute() override;

private:
  User request_;
  Response response_;
};
