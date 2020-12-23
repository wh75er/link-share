#pragma once

#include <string>

#include "response.hpp"
#include "request.hpp"

template<class Model>
class SignUpUserHandler: public BaseHandler<Model> {
public:
  explicit SignUpUserHandler(UserRequest request);
  ~SignUpUserHandler() = default;

  void execute() override;

private:
  UserRequest request_;
};

template<class Model>
SignUpUserHandler<Model>::SignUpUserHandler(UserRequest request):
  request_(request)
{
}

template<class Model>
void SignUpUserHandler<Model>::execute() {
  return;
}
