#pragma once

#include "client.hpp"
#include <memory>
#include <list>


class UserInfo{
public:
    UserInfo();
    UserInfo(std::string& nm, std::string& psw);
    ~UserInfo();

private:
    std::string name;
    std::string password;
};


class Link {
public:
    Link(std::string& name, std::string& url, std::string& tag);
    ~Link();
    std::string addSnapshot();

private:
    std::string linkname;
    std::string url;
    std::vector<std::string> tags;
    std::vector<std::string> snapshotPaths;
};


class Room{
public:
    Room(std::string& roomName, std::string& roomId);
    void addLink(std::string& newLink);
    void removeLink(std::string& linkName);
    void addParticipant(std::string& newPart);
    void removeParticipant(std::string& partName);
    std::string archiveLink(std::string& linkName);
private:
    std::string roomName;
    std::string roomId;
    std::string roomHost;
    std::vector<std::string> participants;
    std::vector<Link> links;
};




class Application {
public:
    Application();
    ~Application();

private:
    Client client;
    UserInfo info;
    std::vector<Room> rooms;
};