#pragma once

#include <memory>

#include "response.hpp"

class BaseHandler {
public:
//  BaseHandler() {};
  virtual ~BaseHandler() {};

  void set_response(std::shared_ptr<Response> response) {
    response_ = response;
  };

  std::shared_ptr<Response> get_response() {
    return response_;
  };

  virtual void execute() = 0;

private:
  std::shared_ptr<Response> response_ = nullptr;
};
