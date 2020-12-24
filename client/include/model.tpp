#pragma once

#include <vector>
#include <iostream>

#include "model.hpp"
#include "requestHandler.hpp"
#include "room.hpp"
#include "userinfo.hpp"
//#include "utils.h"


/* const std::string host = "localhost";
const size_t port = 5555; */

template <class ResponseParser>
class ModelImpl {
public:
    ModelImpl();
    //void passAction(std::string& action, Model& model);

    /* Client& GetClient() {
        return client;
    } */

    std::string formRequest(std::string& action, Model<ResponseParser>& model);
    void handleResponse(std::string& response, Model<ResponseParser>& model);

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
    std::shared_ptr<RequestHandler<ResponseParser>> CreateRequestHandler(std::string& action, Model<ResponseParser>& model);
    std::shared_ptr<RequestHandler<ResponseParser>> currentHandler;


    UserInfo info;
    
    std::shared_ptr<Room> mainRoom;
    std::vector<std::shared_ptr<Room>> rooms;
};

template <class ResponseParser>
ModelImpl<ResponseParser>::ModelImpl() : mainRoom(std::make_shared<Room>("default", "me")) {
}

template <class ResponseParser>
std::shared_ptr<RequestHandler<ResponseParser>> ModelImpl<ResponseParser>::CreateRequestHandler(std::string& action, Model<ResponseParser>& model) {
    std::string::size_type typeEndPos = action.find_first_of(",");
    std::string type = action.substr(0, typeEndPos);

    std::shared_ptr<RequestHandler<ResponseParser>> handler;
    //std::cout << typeEndPos << std::endl;

    switch (atoi(type.c_str()))
    {
    case 1:
        handler = std::make_shared<CreateRoomReqHandler<ResponseParser>>();
        break;
    case 2:
        handler = std::make_shared<RemoveRoomReqHandler<ResponseParser>>();
        break;
    case 3:
        handler = std::make_shared<AddUsersReqHandler<ResponseParser>>();
        break;
    case 4:
        handler = std::make_shared<RemoveUsersReqHandler<ResponseParser>>();
        break;
    case 5:
        handler = std::make_shared<AddLinkReqHandler<ResponseParser>>();
        break;
    case 6:
        handler = std::make_shared<RemoveLinkReqHandler<ResponseParser>>();
        break;
    case 7:
        handler = std::make_shared<ArchiveLinkReqHandler<ResponseParser>>();
        break;
    default:
        break;
    }
    
    handler->FillRequest(action, model);

    return handler;
}


/* void ModelImpl::passAction(std::string& action, Model& model) {
    std::shared_ptr<RequestHandler> handler = CreateRequestHandler(action, model);

    std::string req = handler->GetRequestToSend();
    
    client.writeToServer(req);
    std::string response = client.readFromServer();
    std::cout << std::endl << response << std::endl;
    if (handler->HandleResponse(response) == SUCCESS) {
        handler->DoLogic(model);
    }
} */

template <class ResponseParser>
std::string ModelImpl<ResponseParser>::formRequest(std::string& action, Model<ResponseParser>& model) {
    currentHandler = CreateRequestHandler(action, model);
    std::string req = currentHandler->GetRequestToSend();
    return req;
}

template <class ResponseParser>
void ModelImpl<ResponseParser>::handleResponse(std::string& response, Model<ResponseParser>& model) {
    currentHandler->DoLogic(model);
}

template <class ResponseParser>
Model<ResponseParser>::Model() : modelImpl(new ModelImpl<ResponseParser>) {}
template <class ResponseParser>
Model<ResponseParser>::~Model() {}

template <class ResponseParser>
std::string Model<ResponseParser>::GetMainRoomInfo() {
    std::string ret = modelImpl->GetMainRoom()->GetRoomName() + modelImpl->GetMainRoom()->GetRoomHost();
    return ret;
}

/* void Model::PassAction(std::string& action) {
    modelImpl->passAction(action, *this);
} */

template <class ResponseParser>
std::string Model<ResponseParser>::FormRequest(std::string& action) {
    std::string ret = modelImpl->formRequest(action, *this);
    return ret;
}

template <class ResponseParser>
void Model<ResponseParser>::HandleResponse(std::string& response) {
    modelImpl->handleResponse(response, *this);
}