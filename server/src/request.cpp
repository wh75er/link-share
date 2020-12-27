#include "request.hpp"

RoomRequest::Builder& RoomRequest::Builder::login(std::string& __login) {
  _login = __login;
  return *this;
}

RoomRequest::Builder& RoomRequest::Builder::token(std::string& __token) {
  _token = __token;
  return *this;
}

RoomRequest::Builder& RoomRequest::Builder::name(std::string& __name) {
  _name = __name;
  return *this;
}

RoomRequest::Builder& RoomRequest::Builder::uuid(std::string& __uuid) {
  _uuid = __uuid;
  return *this;
}

RoomRequest::Builder& RoomRequest::Builder::is_private(bool __private) {
  _private = __private;
  return *this;
}

RoomRequest RoomRequest::Builder::build() {
  return RoomRequest(
          _login,
          _token,
          _name,
          _uuid,
          _private
          );
}

LinkRequest::Builder& LinkRequest::Builder::login(std::string& __login) {
  _login = __login;
  return *this;
}

LinkRequest::Builder& LinkRequest::Builder::token(std::string& __token) {
  _token = __token;
  return *this;
}

LinkRequest::Builder& LinkRequest::Builder::uuid(std::string& __uuid) {
  _uuid = __uuid;
  return *this;
}

LinkRequest::Builder& LinkRequest::Builder::url(std::string& __url) {
  _url = __url;
  return *this;
}

LinkRequest::Builder& LinkRequest::Builder::name(std::string& __name) {
  _name = __name;
  return *this;
}

LinkRequest::Builder& LinkRequest::Builder::description(std::string& __description) {
  _description = __description;
  return *this;
}

LinkRequest LinkRequest::Builder::build() {
  return LinkRequest(
          _login,
          _token,
          _uuid,
          _url,
          _name,
          _description
  );
}