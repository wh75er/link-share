#pragma once

#include <string>
#include <memory>

#include "response.hpp"
#include "request.hpp"

template<class Model>
class CreateRoomHandler: public BaseHandler<Model> {
public:
  explicit CreateRoomHandler(RoomRequest request);
  ~CreateRoomHandler() = default;

  void execute() override;

private:
  RoomRequest request_;
};

template<class Model>
CreateRoomHandler<Model>::CreateRoomHandler(RoomRequest request):
        request_(request)
{
}

template<class Model>
void CreateRoomHandler<Model>::execute() {
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

  std::string room_uuid;
  try {
    room_uuid = model->create_room(request_.login, request_.name, request_.private_);
  }
  catch (const std::exception& e) {
    error = e.what();
    response->error = error;
    return;
  }

  response->error = error;
  response->uuid = room_uuid;
}
