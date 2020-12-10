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
    virtual std::shared_ptr<BaseHandler> factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const = 0;
};

template<typename T>
class CreateRoomHandlerCreator : public Creator<T> {
  public:
    std::shared_ptr<BaseHandler> factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const override;
};

template<typename T>
class DeleteRoomHandlerCreator : public Creator<T> {
  public:
    std::shared_ptr<BaseHandler> factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const override;
};

template<typename T>
class AddUserToRoomHandlerCreator : public Creator<T> {
  public:
    std::shared_ptr<BaseHandler> factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const override;
};

template<typename T>
class DeleteUserFromRoomHandlerCreator : public Creator<T> {
  public:
    std::shared_ptr<BaseHandler> factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const override;
};

template<typename T>
class AddLinkHandlerCreator : public Creator<T> {
  public:
    std::shared_ptr<BaseHandler> factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const override;
};

template<typename T>
class DeleteLinkHandlerCreator : public Creator<T> {
  public:
    std::shared_ptr<BaseHandler> factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const override;
};

template<typename T>
class GetSnapshotHandlerCreator : public Creator<T> {
  public:
    std::shared_ptr<BaseHandler> factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const override;
};
