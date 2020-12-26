#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "model.hpp"
#include "requestHandler.hpp"
#include "room.hpp"
#include "userinfo.hpp"
#include "utils.h"


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

    void SetUserInfoFromStr(std::shared_ptr<UserInfo> uinfo) {
        info.swap(uinfo);
        //std::swap(uinfo, info);
    }

    std::string GetUserInfo() {
        return info->getInfoStr();
    }

    void addLink(std::string& linkInfo) {
        mainRoom->addLink(linkInfo);
    }

    void addRoom(std::shared_ptr<Room> newRoom) {
        rooms.push_back(newRoom);
    }

    void removeRoom(const std::string& roomName) {
        auto it = std::find_if(rooms.begin(), rooms.end(),
        [roomName](std::shared_ptr<Room> room) { return room->GetRoomName() == roomName; });
        rooms.erase(it);
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

    std::shared_ptr<UserInfo> info;
    std::shared_ptr<Room> mainRoom;
    std::vector<std::shared_ptr<Room>> rooms;
};

template <class ResponseParser>
ModelImpl<ResponseParser>::ModelImpl()
: info(std::make_shared<UserInfo>()),
 mainRoom(std::make_shared<Room>()) {}

template <class ResponseParser>
std::shared_ptr<RequestHandler<ResponseParser>> ModelImpl<ResponseParser>::CreateRequestHandler(std::string& action, Model<ResponseParser>& model) {
    std::cout << action << std::endl;
    std::string type;
    fillDataFromJson(action, "command", &type);

    std::shared_ptr<RequestHandler<ResponseParser>> handler;

    switch (atoi(type.c_str()) )
    {
    case 0:
        handler = std::make_shared<CreateRoomReqHandler<ResponseParser>>();
        break;
    case 1:
        handler = std::make_shared<RemoveRoomReqHandler<ResponseParser>>();
        break;
    case 2:
        handler = std::make_shared<AddUsersReqHandler<ResponseParser>>();
        break;
    case 3:
        handler = std::make_shared<RemoveUsersReqHandler<ResponseParser>>();
        break;
    case 4:
        handler = std::make_shared<AddLinkReqHandler<ResponseParser>>();
        break;
    case 5:
        handler = std::make_shared<RemoveLinkReqHandler<ResponseParser>>();
        break;
    case 6:
        handler = std::make_shared<ArchiveLinkReqHandler<ResponseParser>>();
        break;
    case 7:
        handler = std::make_shared<LogInReqHandler<ResponseParser>>();
        break;
    case 8:
        handler = std::make_shared<SignUpReqHandler<ResponseParser>>();
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
    if (!currentHandler->HandleResponse(response)) {
        currentHandler->DoLogic(model);
    }
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

template <class ResponseParser>
void Model<ResponseParser>::SetUserInfo(std::shared_ptr<UserInfo> info) {
        modelImpl->SetUserInfoFromStr(info);
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

template <class ResponseParser>
std::string Model<ResponseParser>::GetUserInfo() {
    std::string ret = modelImpl->GetUserInfo();
    return ret;
}

template <class ResponseParser>
void Model<ResponseParser>::AddLink(std::string& linkInfo) {
    modelImpl->addLink(linkInfo);
}


template <class ResponseParser>
void Model<ResponseParser>::AddRoom(std::shared_ptr<Room> newRoom) {
    modelImpl->addRoom(newRoom);
}

template <class ResponseParser>
void Model<ResponseParser>::RemoveRoom(const std::string& roomName) {
    modelImpl->removeRoom(roomName);
}