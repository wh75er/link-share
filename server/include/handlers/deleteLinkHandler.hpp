#pragma once

#include <string>
#include <memory>

#include "response.hpp"
#include "request.hpp"

template<class Model>
class DeleteLinkHandler: public BaseHandler<Model> {
public:
  explicit DeleteLinkHandler(LinkRequest request);
  ~DeleteLinkHandler() = default;

  void execute() override;

private:
  LinkRequest request_;
};

template<class Model>
DeleteLinkHandler<Model>::DeleteLinkHandler(LinkRequest request):
        request_(request)
{
}

template<class Model>
void DeleteLinkHandler<Model>::execute() {
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

  bool verified = false;
  try {
    verified = model->identify(request_.login, request_.token);
  }
  catch (const std::exception& e) {
    error = e.what();
    response->error = error;
    return;
  }

  if (!verified) {
    error = "Authorization error!";
    response->error = error;
    return;
  }

  try {
    model->delete_link(request_.login, request_.uuid);
  }
  catch (const std::exception& e) {
    error = e.what();
    response->error = error;
    return;
  }

  response->error = error;
}
