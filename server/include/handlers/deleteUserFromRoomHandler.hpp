#pragma once

#include <string>
#include <memory>

#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

template<class Model>
class DeleteUserFromRoomHandler: public BaseHandler<Model> {
public:
  explicit DeleteUserFromRoomHandler(UsersRoomRequest request);
  ~DeleteUserFromRoomHandler() = default;

  void execute() override;

private:
  UsersRoomRequest request_;
};

template<class Model>
DeleteUserFromRoomHandler<Model>::DeleteUserFromRoomHandler(UsersRoomRequest request):
        request_(request)
{
}

template<class Model>
void DeleteUserFromRoomHandler<Model>::execute() {
  return;
}
