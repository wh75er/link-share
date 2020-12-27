#pragma once

#include <memory>
#include <string>

#include "link.hpp"

class RoomImpl;

class Room {
public:
    Room();
    Room(std::string& roomName, std::string& roomId, std::string& uuid, bool isPrivate);
    std::string GetRoomInfoStr();
    std::string GetRoomHost();
    std::string GetRoomName();
    std::string GetLinkInfoStr(const std::string& linkName);
    std::string GetLinkSnapshotInfoStr(const std::string& linkName);
    void AddUsers(std::vector<std::string> users);
    void AddSnapshot(const std::string& linkname, const std::string& uuid);
    void RemoveUsers(std::vector<std::string> users);
    void AddLink(std::shared_ptr<Link> newLink);
    void RemoveLink(const std::string& linkName);
    void addParticipant(std::string& newPart);
    void removeParticipant(std::string& partName);
    std::string archiveLink(std::string& linkName);
private:
    std::shared_ptr<RoomImpl> roomImpl;
};

