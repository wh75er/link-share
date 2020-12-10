#pragma once

#include <string>
#include <memory>
#include <vector>
#include <stdexcept>

#include <request.hpp>

enum RequestCommand {
  CREATE_ROOM,
  DELETE_ROOM,
  ADD_USERS,
  DELETE_USERS,
  ADD_LINK,
  DELETE_LINK,
  MAKE_SNAPSHOT,
};

class AbstractBodyParser {
public:
  AbstractBodyParser();
  virtual ~AbstractBodyParser() {};

  virtual std::tuple<int, std::shared_ptr<BaseRequest>> parse(std::string data) = 0;
};

class TcpStringBodyParser : public AbstractBodyParser {
  public:
    TcpStringBodyParser();
    ~TcpStringBodyParser();
    
    std::tuple<int, std::shared_ptr<BaseRequest>> parse(std::string data) override;

  private:
    std::vector<std::string> request_split(std::string& data);

    std::shared_ptr<RoomRequest> form_room_request(std::vector<std::string>& request_elements);
    std::shared_ptr<UsersRoomRequest> form_users_room_request(std::vector<std::string>& request_elements);
    std::shared_ptr<LinkRequest> form_link_request(std::vector<std::string>& request_elements);
    std::shared_ptr<SnapshotRequest> form_snapshot_request(std::vector<std::string>& request_elements);
};
