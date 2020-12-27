#pragma once

#include <memory>
#include <vector>
#include "room.hpp"
#include "userinfo.hpp"


template <class ResponseParser>
class ModelImpl;

template <class ResponseParser>
class Model {
public:
    Model();
    ~Model();
    std::string GetRoomInfoStr(const std::string& roomName);
    std::string GetCurrentRoomInfoStr();
    std::string GetLinkInfoStr(const std::string& linkName);
    void SetUserInfo(std::shared_ptr<UserInfo> info);
    std::string GetUserInfoStr();
    void AddUsers(std::vector<std::string> users);
    void RemoveUsers(std::vector<std::string> users);
    void AddLink(std::shared_ptr<Link> newLink);
    void RemoveLink(const std::string& linkName);
    void AddRoom(std::shared_ptr<Room> newRoom);
    void RemoveRoom(const std::string& roomName);
    std::string FormRequest(std::string& action);
    void HandleResponse(std::string& response);
private:
    std::shared_ptr<ModelImpl<ResponseParser>> modelImpl;
};

#include "model.tpp"