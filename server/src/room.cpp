#include "room.hpp"

Room::Room()
  : id_(0),
    users_(),
    user_(User())
{
}

Room::Room(int id, std::vector<std::string> users, User user)
  : id_(id),
    users_(users),
    user_(user)
{
}

void Room::setId(int id) {
  id_ = id;
}

void Room::setUsers(std::vector<std::string> users) {
  users_ = users;
}

void Room::setUser(User user) {
  user_ = user;
}

int Room::getId() {
  return id_;
}

std::vector<std::string> Room::getUsers() {
  return users_;
}

User Room::getUser() {
  return user_;
}
