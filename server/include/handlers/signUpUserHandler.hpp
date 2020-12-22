#pragma once

#include <string>

#include "user.hpp"
#include "response.hpp"

template<class Model>
class SignUpUserHandler: public BaseHandler<Model> {
public:
  explicit SignUpUserHandler(User &request, Response &response);
  ~SignUpUserHandler() = default;

  void execute() override;

private:
  User& request_;
  Response& response_;
};

template<class Model>
SignUpUserHandler<Model>::SignUpUserHandler(User &request, Response &response)
        : request_(request), response_(response)
{
}

template<class Model>
void SignUpUserHandler<Model>::execute() {
  return;
}
