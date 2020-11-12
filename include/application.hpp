
#include "client.hpp"
#include <memory>
#include <list>


class UserInfo{
public:
    UserInfo();
    UserInfo(std::string nm, std::string psw);
    ~UserInfo();

private:
    std::string name;
    std::string password;
};


class Room{
public:
    Room(std::string roomName);
    void addLink(std::string newLink);
    void removeLink(std::string linkName);
    void addParticipant(std::string newPart);
    void removeParticipant(std::string partName);
    std::string saveMask(std::string linkName);
private:
    std::string roomName;
    std::string roomHost;
    std::vector<std::string> participants;
    std::vector<std::string> links;
};


class Link {
public:
    Link(std::string name, std::string url, std::string tag);
    ~Link();
    std::string addSnapshot();

private:
    std::string linkname;
    std::string url;
    std::vector<std::string> tags;
    std::vector<std::string> snapshotPaths;
};



class Application {
public:
    Application();
    ~Application();
   /*  void logIn(UserInfo inf);
    void logOut();
    void createRoom(std::vector<std::string> participants);
    void addLink(std::string newLink);
    void removeLink(std::string linkName);
 */
private:
    Client client;
    UserInfo info;
    std::vector<Room> rooms;
};