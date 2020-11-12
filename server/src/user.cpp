#include "user.hpp"

User::User()
  : name_(""),
    password_(""),
    token_(""),
    roomId_(0)
{
}

User::User(std::string name, std::string token, int roomId)
  : name_(name),
    password_(""),
    token_(token),
    roomId_(roomId)
{
}

User::User(std::string name, std::string password, std::string token, int roomId)
  : name_(name),
    password_(password),
    token_(token),
    roomId_(roomId)
{
}

void User::setName(std::string name) {
  name_ = name;
}

void User::setPassword(std::string password) {
  password_ = password;
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

std::string User::getPassword() {
  return password_;
}

std::string User::getToken() {
  return token_;
}

int User::getRoomId() {
  return roomId_;
}
