#pragma once

#include <memory>
#include <string>

class RoomImpl;

class Room {
public:
    Room();
    Room(std::string& roomName, std::string& roomId, std::string& uuid, bool isPrivate);
    std::string GetRoomHost();
    std::string GetRoomName();
    void addLink(std::string& linkInfo);
    void removeLink(std::string& linkName);
    void addParticipant(std::string& newPart);
    void removeParticipant(std::string& partName);
    std::string archiveLink(std::string& linkName);
private:
    std::shared_ptr<RoomImpl> roomImpl;
};

/* class PublicRoom : public Room {

};

class PrivateRoom : public Room {

}; */

