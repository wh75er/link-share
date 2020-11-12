#pragma once

#include <string>

#include "handlers/baseHandler.hpp"
#include "user.hpp"
#include "response.hpp"

class SignUpUserHandler: public BaseHandler {
public:
  SignUpUserHandler(User &request, Response &response);
  ~SignUpUserHandler() override {}

  void execute() override;

private:
  User& request_;
  Response& response_;
};
