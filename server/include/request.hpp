#pragma once

#include <string>
#include <vector>

class BaseRequest {
public:
  explicit BaseRequest(std::string &_login, std::string &_token) :
          login(_login),
          token(_token) {
  }

  explicit BaseRequest(std::string &_login) :
          login(_login) {
  }

  virtual ~BaseRequest() = default;

  std::string login;
  std::string token;
};

class RoomRequest : public BaseRequest {
public:
  class Builder;

  explicit RoomRequest(std::string& _login, std::string& _token, std::string& _name, std::string& _uuid, bool& _private):
    BaseRequest(_login, _token),
    name(_name),
    uuid(_uuid),
    private_(_private) {
  }

  ~RoomRequest() override = default;

  std::string name;
  std::string uuid;
  bool private_;
};

class RoomRequest::Builder {
public:
  Builder& login(std::string& __login);
  Builder& token(std::string& __token);
  Builder& name(std::string& __name);
  Builder& uuid(std::string& __uuid);
  Builder& is_private(bool __private);

  RoomRequest build();

private:
  std::string _login = "";
  std::string _token = "";
  std::string _name = "";
  std::string _uuid = "";
  bool _private = false;
};

class UsersRoomRequest : public BaseRequest {
public:
  UsersRoomRequest(std::string& _login, std::string _token, std::string& _uuid, std::vector<std::string>& _participants):
    BaseRequest(_login, _token),
    uuid(_uuid),
    participants(_participants) {
  }

  ~UsersRoomRequest() override = default;

  std::string uuid;
  std::vector<std::string> participants;
};

class LinkRequest : public BaseRequest {
public:
  class Builder;

  LinkRequest(std::string& _login, std::string& _token, std::string& _uuid, std::string& _url, std::string& _name, std::string& _description):
    BaseRequest(_login, _token),
    uuid(_uuid),
    url(_url),
    name(_name),
    description(_description) {
  }

  ~LinkRequest() override = default;

  std::string uuid;
  std::string url;
  std::string name;
  std::string description;
};

class LinkRequest::Builder {
public:
  Builder& login(std::string& __login);
  Builder& token(std::string& __token);
  Builder& uuid(std::string& __uuid);
  Builder& url(std::string& __url);
  Builder& name(std::string& __name);
  Builder& description(std::string& __description);

  LinkRequest build();

private:
  std::string _login = "";
  std::string _token = "";
  std::string _uuid = "";
  std::string _url = "";
  std::string _name = "";
  std::string _description = "";
};

class SnapshotRequest : public BaseRequest {
  public:
    SnapshotRequest(std::string& _login, std::string& _token, std::string& _uuid):
      BaseRequest(_login, _token),
      uuid(_uuid) {
    }

    ~SnapshotRequest() override = default;

    std::string uuid;
};

class UserRequest : public BaseRequest {
public:
  explicit UserRequest(std::string& _login, std::string& _password):
    BaseRequest(_login),
    password(_password)
  {}

  std::string password;
};