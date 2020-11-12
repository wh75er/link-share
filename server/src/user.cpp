#include "user.hpp"

User::User()
  : name_(""),
    token_(""),
    roomId_(0)
{
}

User::User(std::string name, std::string token, int roomId)
  : name_(name),
    token_(token),
    roomId_(roomId)
{
}

void User::setName(std::string name) {
  name_ = name;
}

void User::setToken(std::string token) {
  token_ = token;
}

void User::setRoomId(int roomId) {
  roomId_ = roomId;
}

std::string User::getName() {
  return name_;
}

std::string User::getToken() {
  return token_;
}

int User::getRoomId() {
  return roomId_;
}
