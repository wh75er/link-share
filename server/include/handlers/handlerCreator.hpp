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

class Creator {
  public:
    virtual ~Creator() {};
    virtual std::shared_ptr<BaseHandler> factory_method(BaseRequest& request, Response& response) const = 0;
};

class CreateRoomHandlerCreator : public Creator {
  public:
    std::shared_ptr<BaseHandler> factory_method(BaseRequest& request, Response& response) const override;
};

class DeleteRoomHandlerCreator : public Creator {
  public:
    std::shared_ptr<BaseHandler> factory_method(BaseRequest& request, Response& response) const override;
};

class AddUserToRoomHandlerCreator : public Creator {
  public:
    std::shared_ptr<BaseHandler> factory_method(BaseRequest& request, Response& response) const override;
};

class DeleteUserFromRoomHandlerCreator : public Creator {
  public:
    std::shared_ptr<BaseHandler> factory_method(BaseRequest& request, Response& response) const override;
};

class AddLinkHandlerCreator : public Creator {
  public:
    std::shared_ptr<BaseHandler> factory_method(BaseRequest& request, Response& response) const override;
};

class DeleteLinkHandlerCreator : public Creator {
  public:
    std::shared_ptr<BaseHandler> factory_method(BaseRequest& request, Response& response) const override;
};

class GetSnapshotHandlerCreator : public Creator {
  public:
    std::shared_ptr<BaseHandler> factory_method(BaseRequest& request, Response& response) const override;
};
