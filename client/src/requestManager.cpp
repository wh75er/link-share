#include "model.hpp"
#include "requestManager.hpp"
#include "requestHandler.hpp"

using requestPtr = std::shared_ptr<RequestHandler>;

class RequestManagerImpl {
public:
    RequestManagerImpl();
    void handle(std::string& action, Model& model);
private:
    std::vector<requestPtr> requestList;
};


RequestManagerImpl::RequestManagerImpl() {}
/* 
void RequestManagerImpl::handle(std::string& action, Model& model) {
    std::string::size_type typeEndPos = action.find("#");
    std::string requestType = action.substr(0, typeEndPos);
    
        std::shared_ptr<RequestHandler> handler;
    if (!requestType.compare("AddLink")) {
        handler = std::make_shared<AddLinkReqHandler>();
    } else if (!requestType.compare("RemoveLink")) {
        handler = std::make_shared<RemoveLinkReqHandler>();
    } else if (!requestType.compare("ArchiveLink")) {
        handler = std::make_shared<ArchiveLinkReqHandler>();
    } else if (!requestType.compare("CreateRoom")) {
        handler = std::make_shared<CreateRoomReqHandler>();
    } else if (!requestType.compare("RemoveRoom")) {
        handler = std::make_shared<RemoveRoomReqHandler>();
    }
    handler->FillRequest(action);

} */


RequestManager::RequestManager() : managerImpl(new RequestManagerImpl) {}

RequestManager::~RequestManager() = default;

/* void RequestManager::HandleInput(std::string& action, Model& model) {
    managerImpl->handle(action, model);
} */