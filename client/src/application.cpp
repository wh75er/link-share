#include "application.hpp"

UserInfo::UserInfo() : name(""), password("") {}
UserInfo::UserInfo(std::string& nm, std::string& psw) {}
UserInfo::~UserInfo() {}


Room::Room(std::string& roomName, std::string& roomId) {}
void Room::addLink(std::string& newLink) {}
void Room::removeLink(std::string& linkName) {}
void Room::addParticipant(std::string& newPart) {}
void Room::removeParticipant(std::string& partName) {}
std::string Room::archiveLink(std::string& linkName) {return "str";}



Link::Link(std::string& name, std::string& url, std::string& tag) {}
Link::~Link() {}
std::string Link::addSnapshot() { return "str"; }


Application::Application() : client(), info(), rooms() {}
Application::~Application() {}