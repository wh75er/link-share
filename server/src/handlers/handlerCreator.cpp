#include "handlers/handlerCreator.hpp"

template<typename T>
std::shared_ptr<BaseHandler> CreateRoomHandlerCreator<T>::factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const {
  return std::make_shared<CreateRoomHandler>(request, response);
}

template<typename T>
std::shared_ptr<BaseHandler> DeleteRoomHandlerCreator<T>::factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const {
  return std::make_shared<DeleteRoomHandler>(request, response);
}

template<typename T>
std::shared_ptr<BaseHandler> AddUserToRoomHandlerCreator<T>::factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const {
  return std::make_shared<AddUserToRoomHandler>(request, response);
}

template<typename T>
std::shared_ptr<BaseHandler> DeleteUserFromRoomHandlerCreator<T>::factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const {
  return std::make_shared<DeleteUserFromRoomHandler>(request, response);
}

template<typename T>
std::shared_ptr<BaseHandler> AddLinkHandlerCreator<T>::factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const {
  return std::make_shared<AddLinkHandler>(request, response);
}

template<typename T>
std::shared_ptr<BaseHandler> DeleteLinkHandlerCreator<T>::factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const {
  return std::make_shared<DeleteLinkHandler>(request, response);
}

template<typename T>
std::shared_ptr<BaseHandler> GetSnapshotHandlerCreator<T>::factory_method(std::shared_ptr<T> request, std::shared_ptr<Response> response) const {
  return std::make_shared<GetSnapshotHandler>(request, response);
}
