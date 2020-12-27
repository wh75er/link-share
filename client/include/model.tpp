#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "model.hpp"
#include "room.hpp"
#include "link.hpp"
#include "userinfo.hpp"
#include "requestHandler.hpp"
#include "utils.h"


template <class ResponseParser>
class ModelImpl {
public:
    ModelImpl();

    std::string formRequest(std::string& action, Model<ResponseParser>& model);
    void handleResponse(std::string& response, Model<ResponseParser>& model);
    void handleFile(recFile& newFile);

    void SetUserInfoFromStr(std::shared_ptr<UserInfo> uinfo) {
        info = uinfo;
    }

    std::string getUserInfoStr() {
        return info->getInfoStr();
    }


    std::string getCurrentRoomInfoStr() {
        std::string ret = currentRoom->GetRoomInfoStr();
        return ret;
    }
    
    std::string getLinkInfoStr(const std::string& linkName) {
        std::string ret = currentRoom->GetLinkInfoStr(linkName);
        return ret;
    }

    std::string getLinkSnapshotInfoStr(const std::string& linkName) {
        std::string ret = currentRoom->GetLinkSnapshotInfoStr(linkName);
        return ret;
    }

    std::string getRoomInfoStr(const std::string& roomName) {
        std::string ret;
        for (auto i : rooms) {
            if (i->GetRoomName() == roomName) {
                ret = i->GetRoomInfoStr();
                break;
            }
        }
        if (ret.empty()) {
            throw std::runtime_error("Room is not found");
        }

        return ret;
    }

    void addUsers(std::vector<std::string> users) {
        currentRoom->AddUsers(users);
    }

    void addSnapshotUuid(const std::string& linkname, const std::string& uuid) {
        currentRoom->AddSnapshot(linkname, uuid);
    }

    void removeUsers(std::vector<std::string> users) {
        currentRoom->RemoveUsers(users);
    }

    void addLink(std::shared_ptr<Link> newLink) {
        currentRoom->AddLink(newLink);
    }

    void removeLink(const std::string& linkName) {
        currentRoom->RemoveLink(linkName);
    }

    void addRoom(std::shared_ptr<Room> newRoom) {
        if (currentRoom == nullptr) {
            currentRoom = newRoom;
        } else {
            rooms.push_back(newRoom);
        }
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

    bool isHandlerRecievingFiles() {
        return currentHandler->RecievingFiles();
    }

    bool isServRequired() {
        return currentHandler->ServRequired();
    }
private:
    std::shared_ptr<RequestHandler<ResponseParser>> CreateRequestHandler(std::string& action, Model<ResponseParser>& model);
    std::shared_ptr<RequestHandler<ResponseParser>> currentHandler;

    std::shared_ptr<UserInfo> info;
    std::shared_ptr<Room> mainRoom;
    std::shared_ptr<Room> currentRoom;
    std::vector<std::shared_ptr<Room>> rooms;
};

template <class ResponseParser>
ModelImpl<ResponseParser>::ModelImpl()
: info(nullptr),
 mainRoom(std::make_shared<Room>()),
 currentRoom(nullptr) {}

template <class ResponseParser>
std::shared_ptr<RequestHandler<ResponseParser>> ModelImpl<ResponseParser>::CreateRequestHandler(std::string& action, Model<ResponseParser>& model) {
    std::cout << action << std::endl;
    std::string type;
    fillDataFromJson(action, "command", &type);

    std::shared_ptr<RequestHandler<ResponseParser>> handler;

    switch (atoi(type.c_str()) )
    {
    case 0:
        handler = std::make_shared<CreateRoomReqHandler<ResponseParser>>(false, true);
        break;
    case 1:
        handler = std::make_shared<RemoveRoomReqHandler<ResponseParser>>(false, true);
        break;
    case 2:
        handler = std::make_shared<AddUsersReqHandler<ResponseParser>>(false, true);
        break;
    case 3:
        handler = std::make_shared<RemoveUsersReqHandler<ResponseParser>>(false, true);
        break;
    case 4:
        handler = std::make_shared<AddLinkReqHandler<ResponseParser>>(false, true);
        break;
    case 5:
        handler = std::make_shared<RemoveLinkReqHandler<ResponseParser>>(true, true);
        break;
    case 6:
        handler = std::make_shared<MakeSnapshotReqHandler<ResponseParser>>(true, true);
        break;
    case 7:
        handler = std::make_shared<LogInReqHandler<ResponseParser>>(false, true);
        break;
    case 8:
        handler = std::make_shared<SignUpReqHandler<ResponseParser>>(false, true);
        break;
    case 9:
        handler = std::make_shared<DownloadSnapshotReqHandler<ResponseParser>>(true, true);
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
void ModelImpl<ResponseParser>::handleFile(recFile& newFile) {
    currentHandler->RecieveFile(newFile);
}

template <class ResponseParser>
Model<ResponseParser>::Model() : modelImpl(new ModelImpl<ResponseParser>) {}
template <class ResponseParser>
Model<ResponseParser>::~Model() {}

template <class ResponseParser>
std::string Model<ResponseParser>::GetCurrentRoomInfoStr() {
    std::string ret = modelImpl->getCurrentRoomInfoStr();
    return ret;
}

template <class ResponseParser>
std::string Model<ResponseParser>::GetLinkInfoStr(const std::string& linkName) {
    std::string ret = modelImpl->getLinkInfoStr(linkName);
    return ret;
}

template <class ResponseParser>
std::string Model<ResponseParser>::GetLinkSnapshotInfoStr(const std::string& linkName) {
    std::string ret = modelImpl->getLinkSnapshotInfoStr(linkName);
    return ret;
}

template <class ResponseParser>
std::string Model<ResponseParser>::GetRoomInfoStr(const std::string& roomName) {
    std::string ret = modelImpl->getRoomInfoStr(roomName);
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
void Model<ResponseParser>::HandleFile(recFile& newFile) {
    modelImpl->handleFile(newFile);
}

template <class ResponseParser>
std::string Model<ResponseParser>::GetUserInfoStr() {
    std::string ret = modelImpl->getUserInfoStr();
    return ret;
}

template <class ResponseParser>
void Model<ResponseParser>::AddUsers(std::vector<std::string> users) {
    modelImpl->addUsers(users);
}

template <class ResponseParser>
void Model<ResponseParser>::AddSnapshotUuid(const std::string& linkname, const std::string& uuid) {
    modelImpl->addSnapshotUuid(linkname, uuid);
}

template <class ResponseParser>
void Model<ResponseParser>::RemoveUsers(std::vector<std::string> users) {
    modelImpl->removeUsers(users);
}

template <class ResponseParser>
void Model<ResponseParser>::AddLink(std::shared_ptr<Link> newLink) {
    modelImpl->addLink(newLink);
}


template <class ResponseParser>
void Model<ResponseParser>::RemoveLink(const std::string& linkName) {
    modelImpl->removeLink(linkName);
}

template <class ResponseParser>
void Model<ResponseParser>::AddRoom(std::shared_ptr<Room> newRoom) {
    modelImpl->addRoom(newRoom);
}

template <class ResponseParser>
void Model<ResponseParser>::RemoveRoom(const std::string& roomName) {
    modelImpl->removeRoom(roomName);
}

template <class ResponseParser>
bool Model<ResponseParser>::IsHandlerRecievingFiles() {
    return modelImpl->isHandlerRecievingFiles();
}

template <class ResponseParser>
bool Model<ResponseParser>::IsServRequired() {
    return modelImpl->isServRequired();
}