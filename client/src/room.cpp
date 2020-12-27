#include <vector>

#include "link.hpp"
#include "room.hpp"
#include "utils.h"



class RoomImpl {
public:
    RoomImpl(std::string name, std::string host, std::string uuid, bool isPrivate);
    std::string getRoomInfoStr();
    std::string getRoomHost();
    std::string getRoomName();
    std::string getLinkInfoStr(const std::string& linkName);
    void addUsers(std::vector<std::string> users);
    void removeUsers(std::vector<std::string> users);
    void addLink(std::shared_ptr<Link> newLink);
    void removeLink(const std::string& linkName);
    void addParticipant(std::string& newPart);
    void removeParticipant(std::string& partName);
    std::string archiveLink(std::string& linkName);

private:
    std::string roomName = "";
    std::string roomHost = "";
    std::string uuid = "";
    bool isPrivate  = true;
    std::vector<std::string> participants;
    std::vector<std::shared_ptr<Link>> links;
};


Room::Room() {}

Room::Room(std::string& name, std::string& host, std::string& uuid, bool isPrivate)
: roomImpl(new RoomImpl(name, host, uuid, isPrivate)) {}

std::string Room::GetRoomInfoStr() {
    return roomImpl->getRoomInfoStr();
}

std::string Room::GetRoomHost() {
    std::string ret = roomImpl->getRoomHost();
    return ret;
}
std::string Room::GetRoomName() {
    std::string ret = roomImpl->getRoomName();
    return ret;
}

std::string Room::GetLinkInfoStr(const std::string& linkName) {
    std::string ret = roomImpl->getLinkInfoStr(linkName);
    return ret;
}

void Room::AddUsers(std::vector<std::string> users) {
    roomImpl->addUsers(users);
}

void Room::RemoveUsers(std::vector<std::string> users) {
    roomImpl->removeUsers(users);
}

void Room::AddLink(std::shared_ptr<Link> newLink) {
    roomImpl->addLink(newLink);
}

void Room::RemoveLink(const std::string& linkName) {
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

std::string RoomImpl::getRoomInfoStr() {
    std::string ret = packToJsonString("name", roomName, "password", roomHost, "uuid", uuid, "private", isPrivate);
    return ret;
}

std::string RoomImpl::getRoomHost() {
    return roomHost;
}

std::string RoomImpl::getRoomName() {
    return roomName;
}

std::string RoomImpl::getLinkInfoStr(const std::string& linkName) {
    std::string ret;
    for(auto i : links) {
        if (i->GetLinkName() == linkName) {
            ret = i->GetLinkInfo();
        }
    }
    if (ret.empty()) {
        throw std::runtime_error("Link was not found");;
    }
    return ret;
}

void RoomImpl::addUsers(std::vector<std::string> users) {
    for (auto i : users) {
        auto it = std::find(participants.begin(), participants.end(), i);
        if (it == participants.end()) {
            participants.push_back(i);
        }
    }
}

void RoomImpl::removeUsers(std::vector<std::string> users) {
    for (auto i : users) {
        participants.erase(std::remove(participants.begin(), participants.end(), i), participants.end());
    }
}

void RoomImpl::addLink(std::shared_ptr<Link> newLink) {
    links.push_back(newLink);
}

void RoomImpl::removeLink(const std::string& linkName) {

    auto it = std::find_if(links.begin(), links.end(),
        [linkName](std::shared_ptr<Link> link) { return link->GetLinkName() == linkName; });
    links.erase(it);

}


void RoomImpl::addParticipant(std::string& newPart) {}
void RoomImpl::removeParticipant(std::string& partName) {}
std::string RoomImpl::archiveLink(std::string& linkName) { return "str"; }