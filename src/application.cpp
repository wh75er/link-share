#include "application.hpp"


UserInfo::UserInfo() {}
UserInfo::UserInfo(std::string nm, std::string psw) {}
UserInfo::~UserInfo() {}


Room::Room(std::string roomName) {}
void Room::addLink(std::string newLink) {}
void Room::removeLink(std::string linkName) {}
void Room::addParticipant(std::string newPart) {}
void Room::removeParticipant(std::string partName) {}
std::string Room::saveMask(std::string linkName) {}



Link::Link(std::string name, std::string url, std::string tag) {}
Link::~Link() {}
std::string Link::addSnapshot() {}


Application::Application() {}
Application::~Application() {}