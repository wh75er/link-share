#pragma once

#include <string>
#include <memory>

#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

template<class Model>
class AddLinkHandler: public BaseHandler<Model> {
public:
  explicit AddLinkHandler(LinkRequest request);
  ~AddLinkHandler() = default;

  void execute() override;

private:
  LinkRequest request_;
};

template<class Model>
AddLinkHandler<Model>::AddLinkHandler(LinkRequest request):
        request_(request)
{
}

template<class Model>
void AddLinkHandler<Model>::execute() {
  std::string error = "";

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

  std::string link_uuid;
  try {
    link_uuid = model->create_link(request_.url, request_.name, request_.description, request_.uuid);
  }
  catch (const std::exception& e) {
    error = e.what();
    response->error = error;
    return;
  }

  response->error = error;
  response->uuid = link_uuid;
}
