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
  }

  try {
    model->sign_up_user(request_.login, request_.password);
  }
  catch (const std::exception& e) {
    error = e.what();
    response->error = error;
    return;
  }

  response->error = error;
}
