#include <vector>
#include <iostream>

#include "model.hpp"
#include "requestManager.hpp"
#include "requestHandler.hpp"
#include "room.hpp"
#include "userinfo.hpp"


const std::string host = "localhost";
const size_t port = 5555;

class ModelImpl {
public:
    ModelImpl();
    void passAction(std::string& action, Model& model);

    Client& GetClient() {
        return client;
    }


    UserInfo& GetUserInfo() {
        return info;
    }

    std::shared_ptr<Room> GetMainRoom() {
        return mainRoom;
    }

    std::vector<std::shared_ptr<Room>> GetRooms() {
        return rooms;
    }
private:
    std::shared_ptr<RequestHandler> CreateRequestHandler(std::string& action, Model& model);

    Client client;
    UserInfo info;
    
    std::shared_ptr<Room> mainRoom;
    std::vector<std::shared_ptr<Room>> rooms;
};

ModelImpl::ModelImpl() : client(host, port) {
    client.Connect();
}

std::shared_ptr<RequestHandler> ModelImpl::CreateRequestHandler(std::string& action, Model& model) {
    std::string::size_type typeEndPos = action.find_first_of(",");
    std::string type = action.substr(0, typeEndPos);

    std::shared_ptr<RequestHandler> handler;
    //std::cout << typeEndPos << std::endl;

    switch (atoi(type.c_str()))
    {
    case 1:
        handler = std::make_shared<CreateRoomReqHandler>();
        break;
    case 2:
        handler = std::make_shared<RemoveRoomReqHandler>();
        break;
    case 3:
        handler = std::make_shared<AddUsersReqHandler>();
        break;
    case 4:
        handler = std::make_shared<RemoveUsersReqHandler>();
        break;
    case 5:
        handler = std::make_shared<AddLinkReqHandler>();
        break;
    case 6:
        handler = std::make_shared<RemoveLinkReqHandler>();
        break;
    case 7:
        handler = std::make_shared<ArchiveLinkReqHandler>();
        break;
    default:
        break;
    }
    
    handler->FillRequest(action, model);

    return handler;
}

void ModelImpl::passAction(std::string& action, Model& model) {
    
    std::shared_ptr<RequestHandler> handler = CreateRequestHandler(action, model);

    std::string req = handler->GetRequestToSend();
    
    //std::cout << "req: " << req;

    client.writeToServer(req);
    //std::cout << "*********" << std::endl;
    std::string response = client.readFromServer();
    std::cout << response;
    if (handler->HandleResponse(response) == SUCCESS) {
        handler->DoLogic(model);
    }
}

Model::Model() : modelImpl(new ModelImpl) {}
Model::~Model() {}

std::string Model::GetMainRoomInfo() {
    std::string ret = modelImpl->GetMainRoom()->GetRoomName() + modelImpl->GetMainRoom()->GetRoomHost();
    return ret;
}

void Model::PassAction(std::string& action) {
    modelImpl->passAction(action, *this);
}