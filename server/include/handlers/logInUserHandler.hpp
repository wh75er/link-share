#pragma once

#include <string>

#include "user.hpp"
#include "response.hpp"

template<class Model>
class LogInUserHandler: public BaseHandler<Model> {
public:
  explicit LogInUserHandler(User &request, Response &response);
  ~LogInUserHandler() = default;

  void execute() override;

private:
  User& request_;
  Response& response_;
};

template<class Model>
LogInUserHandler<Model>::LogInUserHandler(User &request, Response &response)
        : request_(request), response_(response)
{
}

template<class Model>
void LogInUserHandler<Model>::execute() {
  return;
}
