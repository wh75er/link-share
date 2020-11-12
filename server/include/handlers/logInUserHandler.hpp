#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "user.hpp"
#include "response.hpp"

class LogInUserHandler: public BaseHandler {
public:
  LogInUserHandler(User &request, Response &response);
  ~LogInUserHandler() override {}

  void execute() override;

private:
  User& request_;
  Response& response_;
};
