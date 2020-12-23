#pragma once

#include <string>

#include "response.hpp"
#include "request.hpp"

template<class Model>
class LogInUserHandler: public BaseHandler<Model> {
public:
  explicit LogInUserHandler(UserRequest request);
  ~LogInUserHandler() = default;

  void execute() override;

private:
  UserRequest request_;
};

template<class Model>
LogInUserHandler<Model>::LogInUserHandler(UserRequest request):
  request_(request)
{
}

template<class Model>
void LogInUserHandler<Model>::execute() {
  return;
}
