#pragma once

#include <string>
#include <memory>

#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

template<class Model>
class DeleteRoomHandler: public BaseHandler<Model> {
public:
  explicit DeleteRoomHandler(RoomRequest request);
  ~DeleteRoomHandler() = default;

  void execute() override;

private:
  RoomRequest request_;
};

template<class Model>
DeleteRoomHandler<Model>::DeleteRoomHandler(RoomRequest request):
        request_(request)
{
}

template<class Model>
void DeleteRoomHandler<Model>::execute() {
  return;
}
