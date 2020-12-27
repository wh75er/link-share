#pragma once

#include <string>
#include <memory>

#include "response.hpp"
#include "request.hpp"

template<class Model>
class GetSnapshotHandler: public BaseHandler<Model> {
public:
  explicit GetSnapshotHandler(SnapshotRequest request);
  ~GetSnapshotHandler() = default;

  void execute() override;

private:
  SnapshotRequest request_;
};

template<class Model>
GetSnapshotHandler<Model>::GetSnapshotHandler(SnapshotRequest request):
        request_(request)
{
}

template<class Model>
void GetSnapshotHandler<Model>::execute() {
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

  std::string files_dir;
  try {
    files_dir = model->get_snapshot(request_.login, request_.uuid);
  }
  catch (const std::exception& e) {
    error = e.what();
    response->error = error;
    return;
  }

  response->error = error;
  response->files_dir = files_dir;
}
