#include <vector>

#include "link.hpp"
#include "room.hpp"
#include "utils.h"



class RoomImpl {
public:
    RoomImpl(std::string name, std::string host, std::string uuid, bool isPrivate);
    std::string getRoomHost();
    std::string getRoomName();
    void addLink(std::string& linkInfo);
    void removeLink(std::string& linkName);
    void addParticipant(std::string& newPart);
    void removeParticipant(std::string& partName);
    std::string archiveLink(std::string& linkName);

private:
    std::string roomName = "";
    std::string roomHost = "";
    std::string uuid = "";
    bool isPrivate  = true;
    std::vector<std::string> participants;
    std::vector<Link> links;
};


Room::Room() {}

Room::Room(std::string& name, std::string& host, std::string& uuid, bool isPrivate)
: roomImpl(new RoomImpl(name, host, uuid, isPrivate)) {}
std::string Room::GetRoomHost() {
    std::string ret = roomImpl->getRoomHost();
    return ret;
}
std::string Room::GetRoomName() {
    std::string ret = roomImpl->getRoomName();
    return ret;
}

void Room::addLink(std::string& linkInfo) {
    roomImpl->addLink(linkInfo);
}

void Room::removeLink(std::string& linkName) {
    roomImpl->removeLink(linkName);
}

void Room::addParticipant(std::string& newPart) {}
void Room::removeParticipant(std::string& partName) {}

std::string Room::archiveLink(std::string& linkName) {
    return "str";
}


RoomImpl::RoomImpl(std::string name, std::string host, std::string uuid, bool isPrivate)
: roomName(name),
roomHost(host),
uuid(uuid),
isPrivate(isPrivate) {}

std::string RoomImpl::getRoomHost() {
    return roomHost;
}

std::string RoomImpl::getRoomName() {
    return roomName;
}

void RoomImpl::addLink(std::string& linkInfo) {
    std::string name, url, uuid;
    fillDataFromJson(linkInfo, "name", &name, "url", &url, "uuid", &uuid);
    Link newLink(name, url, uuid);
    links.push_back(std::move(newLink));
}

void RoomImpl::removeLink(std::string& linkName) {

    /* for(std::vector<Link>::iterator it = links.begin(); it != links.end(); ++it) {
        if ((*it).GetLinkName() == linkName) {
            links.erase(it);
        }
    } */
}


void RoomImpl::addParticipant(std::string& newPart) {}
void RoomImpl::removeParticipant(std::string& partName) {}
std::string RoomImpl::archiveLink(std::string& linkName) { return "str"; }