#pragma once

#include <string>
#include <memory>

#include "room.hpp"
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
  return;
}
