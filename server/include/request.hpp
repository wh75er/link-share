#pragma once

#include <string>
#include <vector>

class BaseRequest {
  public:
    BaseRequest() {};
    virtual ~BaseRequest() {};
};

class RoomRequest : public BaseRequest {
  public:
    explicit RoomRequest(std::string& _room_name, std::string& _room_host):
      room_name(_room_name),
      room_host(_room_host)
      {}
    ~RoomRequest() {};

    std::string room_name;
    std::string room_host;
};

class UsersRoomRequest : public BaseRequest {
  public:
    UsersRoomRequest(std::string& _room_name, std::string& _room_host, std::vector<std::string>& _participants):
      room_name(_room_name),
      room_host(_room_host),
      participiants(_participants)
      {}
    ~UsersRoomRequest() {};

    std::string room_name;
    std::string room_host;
    std::vector<std::string> participiants;
};

class LinkRequest : public BaseRequest {
  public:
    LinkRequest(std::string& _room_name, std::string& _room_host, std::string& _url):
      room_name(_room_name),
      room_host(_room_host),
      url(_url)
      {}
    ~LinkRequest() {};
    
    std::string room_name;
    std::string room_host;
    std::string url;
};

class SnapshotRequest : public BaseRequest {
  public:
    SnapshotRequest(std::string& _room_name, std::string& _room_host, std::string& _url_id):
      room_name(_room_name),
      room_host(_room_host),
      url_id(_url_id)
      {}
    ~SnapshotRequest() {};

    std::string room_name;
    std::string room_host;
    std::string url_id;
};
