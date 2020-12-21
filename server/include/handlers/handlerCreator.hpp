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
#include "handlers/getSnapshotHandler.hpp"

template<typename T>
class Creator {
public:
  virtual ~Creator() = default;
  virtual std::shared_ptr<BaseHandler> factory_method(T request) const = 0;
};

template<typename T>
class CreateRoomHandlerCreator : public Creator<T> {
public:
  CreateRoomHandlerCreator() = default;
  ~CreateRoomHandlerCreator() = default;

  std::shared_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_shared<CreateRoomHandler>(request);
  }
};

template<typename T>
class DeleteRoomHandlerCreator : public Creator<T> {
public:
  DeleteRoomHandlerCreator() = default;
  ~DeleteRoomHandlerCreator() = default;

  std::shared_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_shared<DeleteRoomHandler>(request);
  }
};

template<typename T>
class AddUserToRoomHandlerCreator : public Creator<T> {
public:
  AddUserToRoomHandlerCreator() = default;
  ~AddUserToRoomHandlerCreator() = default;

  std::shared_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_shared<AddUserToRoomHandler>(request);
  }
};

template<typename T>
class DeleteUserFromRoomHandlerCreator : public Creator<T> {
public:
  DeleteUserFromRoomHandlerCreator() = default;
  ~DeleteUserFromRoomHandlerCreator() = default;

  std::shared_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_shared<DeleteUserFromRoomHandler>(request);
  }
};

template<typename T>
class AddLinkHandlerCreator : public Creator<T> {
public:
  AddLinkHandlerCreator() = default;
  ~AddLinkHandlerCreator() = default;

  std::shared_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_shared<AddLinkHandler>(request);
  }
};

template<typename T>
class DeleteLinkHandlerCreator : public Creator<T> {
public:
  DeleteLinkHandlerCreator() = default;
  ~DeleteLinkHandlerCreator() = default;

  std::shared_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_shared<DeleteLinkHandler>(request);
  }
};

template<typename T>
class GetSnapshotHandlerCreator : public Creator<T> {
public:
  GetSnapshotHandlerCreator() = default;
  ~GetSnapshotHandlerCreator() = default;

  std::shared_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_shared<GetSnapshotHandler>(request);
  }
};
