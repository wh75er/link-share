#pragma once

#include <string>
#include <memory>

#include "room.hpp"
#include "response.hpp"
#include "request.hpp"

template<class Model>
class AddUserToRoomHandler: public BaseHandler<Model> {
public:
  explicit AddUserToRoomHandler(UsersRoomRequest request);
  ~AddUserToRoomHandler() = default;

  void execute() override;

private:
  UsersRoomRequest request_;
};

template<class Model>
AddUserToRoomHandler<Model>::AddUserToRoomHandler(UsersRoomRequest request):
        request_(request)
{
}

template<class Model>
void AddUserToRoomHandler<Model>::execute() {
  return;
}
