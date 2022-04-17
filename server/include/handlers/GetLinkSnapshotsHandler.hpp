#pragma once

#include <string>

#include "response.hpp"
#include "request.hpp"

template<class Model>
class GetLinkSnapshotsHandler: public BaseHandler<Model> {
public:
  explicit GetLinkSnapshotsHandler(SnapshotRequest request);
  ~GetLinkSnapshotsHandler() = default;

  void execute() override;

private:
  SnapshotRequest request_;
};

template<class Model>
GetLinkSnapshotsHandler<Model>::GetLinkSnapshotsHandler(SnapshotRequest request):
  request_(request)
{
}

template<class Model>
void GetLinkSnapshotsHandler<Model>::execute() {
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

  std::vector<std::map<std::string, std::string>> link_snapshots;
  try {
    link_snapshots = model->get_link_snapshots(request_.uuid);
  }
  catch (const std::exception& e) {
    error = e.what();
    response->error = error;
    return;
  }

  response->error = error;
  response->objects = link_snapshots;
}
