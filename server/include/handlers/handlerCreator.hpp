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
  virtual ~Creator() {};
  virtual std::unique_ptr<BaseHandler> factory_method(T request) const = 0;
};

template<typename T>
class CreateRoomHandlerCreator : public Creator<T> {
public:
  CreateRoomHandlerCreator() = default;
  ~CreateRoomHandlerCreator() = default;

  std::unique_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_unique<CreateRoomHandler>(request);
  }
};

template<typename T>
class DeleteRoomHandlerCreator : public Creator<T> {
public:
  DeleteRoomHandlerCreator() = default;
  ~DeleteRoomHandlerCreator() = default;

  std::unique_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_unique<DeleteRoomHandler>(request);
  }
};

template<typename T>
class AddUserToRoomHandlerCreator : public Creator<T> {
public:
  AddUserToRoomHandlerCreator() = default;
  ~AddUserToRoomHandlerCreator() = default;

  std::unique_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_unique<AddUserToRoomHandler>(request);
  }
};

template<typename T>
class DeleteUserFromRoomHandlerCreator : public Creator<T> {
public:
  DeleteUserFromRoomHandlerCreator() = default;
  ~DeleteUserFromRoomHandlerCreator() = default;

  std::unique_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_unique<DeleteUserFromRoomHandler>(request);
  }
};

template<typename T>
class AddLinkHandlerCreator : public Creator<T> {
public:
  AddLinkHandlerCreator() = default;
  ~AddLinkHandlerCreator() = default;

  std::unique_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_unique<AddLinkHandler>(request);
  }
};

template<typename T>
class DeleteLinkHandlerCreator : public Creator<T> {
public:
  DeleteLinkHandlerCreator() = default;
  ~DeleteLinkHandlerCreator() = default;

  std::unique_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_unique<DeleteLinkHandler>(request);
  }
};

template<typename T>
class GetSnapshotHandlerCreator : public Creator<T> {
public:
  GetSnapshotHandlerCreator() = default;
  ~GetSnapshotHandlerCreator() = default;

  std::unique_ptr<BaseHandler> factory_method(T request) const override {
    return std::make_unique<GetSnapshotHandler>(request);
  }
};
