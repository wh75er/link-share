#pragma once

#include <memory>
#include <vector>
#include "room.hpp"
#include "userinfo.hpp"


typedef struct recFile
{
    std::string name;
    std::vector<char> body;
} recFile;


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
    std::string GetLinkSnapshotInfoStr(const std::string& linkName);
    void SetUserInfo(std::shared_ptr<UserInfo> info);
    std::string GetUserInfoStr();
    void AddUsers(std::vector<std::string> users);
    void AddSnapshotUuid(const std::string& linkname, const std::string& uuid);
    void RemoveUsers(std::vector<std::string> users);
    void AddLink(std::shared_ptr<Link> newLink);
    void RemoveLink(const std::string& linkName);
    void AddRoom(std::shared_ptr<Room> newRoom);
    void RemoveRoom(const std::string& roomName);
    std::string FormRequest(std::string& action);
    void HandleResponse(std::string& response);
    void HandleFile(recFile& newFile);
    bool IsHandlerRecievingFiles();
    bool IsServRequired();
private:
    std::shared_ptr<ModelImpl<ResponseParser>> modelImpl;
};

#include "model.tpp"