#pragma once

#include <memory>

#include "request.hpp"
#include "response.hpp"

#include "handlers/baseHandler.hpp"
#include "handlers/createRoomHandler.hpp"
#include "handlers/deleteRoomHandler.hpp"
#include "handlers/addUserToRoomHandler.hpp"
#include "handlers/deleteUserFromRoomHandler.hpp"
#include "handlers/addLinkHandler.hpp"
#include "handlers/deleteLinkHandler.hpp"
#include "handlers/createSnapshotHandler.hpp"
#include "handlers/logInUserHandler.hpp"
#include "handlers/signUpUserHandler.hpp"
#include "handlers/getSnapshotHandler.hpp"

template<typename T, class Model>
class Creator {
public:
  virtual ~Creator() = default;
  virtual std::shared_ptr<BaseHandler<Model>> factory_method(T request) const = 0;
};

template<typename T, class Model>
class CreateRoomHandlerCreator : public Creator<T, Model> {
public:
  CreateRoomHandlerCreator() = default;
  ~CreateRoomHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<CreateRoomHandler<Model>>(request);
  }
};

template<typename T, class Model>
class DeleteRoomHandlerCreator : public Creator<T, Model> {
public:
  DeleteRoomHandlerCreator() = default;
  ~DeleteRoomHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<DeleteRoomHandler<Model>>(request);
  }
};

template<typename T, class Model>
class AddUserToRoomHandlerCreator : public Creator<T, Model> {
public:
  AddUserToRoomHandlerCreator() = default;
  ~AddUserToRoomHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<AddUserToRoomHandler<Model>>(request);
  }
};

template<typename T, class Model>
class DeleteUserFromRoomHandlerCreator : public Creator<T, Model> {
public:
  DeleteUserFromRoomHandlerCreator() = default;
  ~DeleteUserFromRoomHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<DeleteUserFromRoomHandler<Model>>(request);
  }
};

template<typename T, class Model>
class AddLinkHandlerCreator : public Creator<T, Model> {
public:
  AddLinkHandlerCreator() = default;
  ~AddLinkHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<AddLinkHandler<Model>>(request);
  }
};

template<typename T, class Model>
class DeleteLinkHandlerCreator : public Creator<T, Model> {
public:
  DeleteLinkHandlerCreator() = default;
  ~DeleteLinkHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<DeleteLinkHandler<Model>>(request);
  }
};

template<typename T, class Model>
class CreateSnapshotHandlerCreator : public Creator<T, Model> {
public:
  CreateSnapshotHandlerCreator() = default;
  ~CreateSnapshotHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<CreateSnapshotHandler<Model>>(request);
  }
};

template<typename T, class Model>
class GetLogInUserHandlerCreator : public Creator<T, Model> {
public:
  GetLogInUserHandlerCreator() = default;
  ~GetLogInUserHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<LogInUserHandler<Model>>(request);
  }
};

template<typename T, class Model>
class GetSignUpUserHandlerCreator : public Creator<T, Model> {
public:
  GetSignUpUserHandlerCreator() = default;
  ~GetSignUpUserHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<SignUpUserHandler<Model>>(request);
  }
};

template<typename T, class Model>
class GetSnapshotHandlerCreator : public Creator<T, Model> {
public:
  GetSnapshotHandlerCreator() = default;
  ~GetSnapshotHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<GetSnapshotHandler<Model>>(request);
  }
};

template<typename T, class Model>
class GetUserRoomHandlerCreator : public Creator<T, Model> {
public:
  GetUserRoomHandlerCreator() = default;
  ~GetUserRoomHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<GetUserRoomHandler<Model>>(request);
  }
};

template<typename T, class Model>
class GetUserLinksHandlerCreator : public Creator<T, Model> {
public:
  GetUserLinksHandlerCreator() = default;
  ~GetUserLinksHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<GetUserLinksHandler<Model>>(request);
  }
};

template<typename T, class Model>
class GetLinkSnapshotsHandlerCreator : public Creator<T, Model> {
public:
  GetLinkSnapshotsHandlerCreator() = default;
  ~GetLinkSnapshotsHandlerCreator() = default;

  std::shared_ptr<BaseHandler<Model>> factory_method(T request) const override {
    return std::make_shared<GetLinkSnapshotsHandler<Model>>(request);
  }
};
