#pragma once

#include <string>

#include "handlers/baseHandler.hpp"

class SignUpUserHandler: BaseHandler {
public:
  SignUpUserHandler(User &request, Response &response);
  ~SignUpUserHandler() override;

  void execute() override;

private:
  User request_;
  Response response_;
};
