#include "handlers/handlerCreator.hpp"

std::shared_ptr<BaseHandler> CreateRoomHandlerCreator::factory_method(BaseRequest& request, Response& response) const {
  return std::make_shared<CreateRoomHandler>(request, response);
}

std::shared_ptr<BaseHandler> DeleteRoomHandlerCreator::factory_method(BaseRequest& request, Response& response) const {
  return std::make_shared<DeleteRoomHandler>(request, response);
}

std::shared_ptr<BaseHandler> AddUserToRoomHandlerCreator::factory_method(BaseRequest& request, Response& response) const {
  return std::make_shared<AddUserToRoomHandler>(request, response);
}

std::shared_ptr<BaseHandler> DeleteUserFromRoomHandlerCreator::factory_method(BaseRequest& request, Response& response) const {
  return std::make_shared<DeleteUserFromRoomHandler>(request, response);
}

std::shared_ptr<BaseHandler> AddLinkHandlerCreator::factory_method(BaseRequest& request, Response& response) const {
  return std::make_shared<AddLinkHandler>(request, response);
}

std::shared_ptr<BaseHandler> DeleteLinkHandlerCreator::factory_method(BaseRequest& request, Response& response) const {
  return std::make_shared<DeleteLinkHandler>(request, response);
}

std::shared_ptr<BaseHandler> GetSnapshotHandlerCreator::factory_method(BaseRequest& request, Response& response) const {
  return std::make_shared<GetSnapshotHandler>(request, response);
}
