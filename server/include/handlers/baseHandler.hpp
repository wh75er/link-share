#pragma once

#include <memory>

#include "response.hpp"

template<class Model>
class BaseHandler {
public:
//  BaseHandler() {};
  virtual ~BaseHandler() = default;

  void set_model(std::shared_ptr<Model> _model) {
    model = _model;
  }

  std::shared_ptr<Model> get_model() {
    return model;
  }

  void set_response(std::shared_ptr<Response> response) {
    response_ = response;
  };

  std::shared_ptr<Response> get_response() {
    return response_;
  };

  virtual void execute() = 0;

protected:
  std::shared_ptr<Model> model = nullptr;

private:
  std::shared_ptr<Response> response_ = nullptr;
};

#include "addLinkHandler.hpp"
#include "addUserToRoomHandler.hpp"
#include "createRoomHandler.hpp"
#include "deleteLinkHandler.hpp"
#include "deleteRoomHandler.hpp"
#include "deleteUserFromRoomHandler.hpp"
#include "getSnapshotHandler.hpp"
#include "logInUserHandler.hpp"
#include "signUpUserHandler.hpp"