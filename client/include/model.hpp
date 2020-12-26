#pragma once

#include <memory>
#include "room.hpp"
#include "userinfo.hpp"


template <class ResponseParser>
class ModelImpl;

template <class ResponseParser>
class Model {
public:
    Model();
    ~Model();
    std::string GetMainRoomInfo();
    //void PassAction(std::string& action);
    void SetUserInfo(std::shared_ptr<UserInfo> info);
    std::string GetUserInfo();
    void AddLink(std::string& linkInfo);
    void AddRoom(std::shared_ptr<Room> newRoom);
    void RemoveRoom(const std::string& roomName);
    std::string FormRequest(std::string& action);
    void HandleResponse(std::string& response);
private:
    std::shared_ptr<ModelImpl<ResponseParser>> modelImpl;
};

#include "model.tpp"