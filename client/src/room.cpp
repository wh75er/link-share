#include <vector>

#include "link.hpp"
#include "room.hpp"



class RoomImpl {
public:
    RoomImpl(std::string name, std::string host);
    std::string getRoomHost();
    std::string getRoomName();
    void addLink(std::string& name, std::string url);
    void removeLink(std::string& linkName);
    void addParticipant(std::string& newPart);
    void removeParticipant(std::string& partName);
    std::string archiveLink(std::string& linkName);

private:
    std::string roomName;
    /* std::string roomId; */
    std::string roomHost;
    std::vector<std::string> participants;
    std::vector<Link> links;
};


Room::Room(std::string name, std::string host) : roomImpl(new RoomImpl(name, host)) {}
std::string Room::GetRoomHost() {
    std::string ret = roomImpl->getRoomHost();
    return ret;
}
std::string Room::GetRoomName() {
    std::string ret = roomImpl->getRoomName();
    return ret;
}

void Room::addLink(std::string& name, std::string& url) {
    roomImpl->addLink(name, url);
}

void Room::removeLink(std::string& linkName) {
    roomImpl->removeLink(linkName);
}

void Room::addParticipant(std::string& newPart) {}
void Room::removeParticipant(std::string& partName) {}

std::string Room::archiveLink(std::string& linkName) {
    return "str";
}


RoomImpl::RoomImpl(std::string name, std::string host) : roomName(name), roomHost(host) {}

std::string RoomImpl::getRoomHost() {
    return roomHost;
}

std::string RoomImpl::getRoomName() {
    return roomName;
}

void RoomImpl::addLink(std::string& name, std::string url) {
    Link newLink(name, url);
    links.push_back(std::move(newLink));
}

void RoomImpl::removeLink(std::string& linkName) {
    for(std::vector<Link>::iterator it = links.begin(); it != links.end(); ++it) {
        if ((*it).GetLinkName() == linkName) {
            links.erase(it);
        }
    }
}

void RoomImpl::addParticipant(std::string& newPart) {}
void RoomImpl::removeParticipant(std::string& partName) {}
std::string RoomImpl::archiveLink(std::string& linkName) { return "str"; }