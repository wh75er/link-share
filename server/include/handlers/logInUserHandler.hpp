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
  std::string error;

  std::shared_ptr<Model> model = this->get_model();
  std::shared_ptr<Response> response = this->get_response();

  if (!model) {
    error = "Model is not set!";
    response->error = error;
    return;
  }

  if(!response) {
    this->set_response(std::make_shared<Response>());
    response = this->get_response();
  }

  std::string token;
  try {
    token = model->generate_token(request_.login, request_.password);
  }
  catch (const std::exception& e) {
    error = e.what();
    response->error = error;
    return;
  }

  response->error = error;
  response->uuid = token;
}
