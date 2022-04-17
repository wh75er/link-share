#pragma once

#include <string>

#include "response.hpp"
#include "request.hpp"

template<class Model>
class GetUserLinksHandler: public BaseHandler<Model> {
public:
  explicit GetUserLinksHandler(SnapshotRequest request);
  ~GetUserLinksHandler() = default;

  void execute() override;

private:
  SnapshotRequest request_;
};

template<class Model>
GetUserLinksHandler<Model>::GetUserLinksHandler(SnapshotRequest request):
  request_(request)
{
}

template<class Model>
void GetUserLinksHandler<Model>::execute() {
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

  std::vector<std::map<std::string, std::string>> room_links;
  try {
    room_links = model->get_room_links(request_.uuid);
  }
  catch (const std::exception& e) {
    error = e.what();
    response->error = error;
    return;
  }

  response->error = error;
  response->objects = room_links;
}
