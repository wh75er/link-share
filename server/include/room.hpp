#pragma once

#include <string>
#include <vector>

#include "user.hpp"

class Room {
public:
  Room(int id, std::vector<std::string> users, User user);
  ~Room() {};

  void setId(int id);
  void setUsers(std::vector<std::string> users);
  void setUser(User user);

  int getId();
  std::vector<std::string> getUsers();
  User getUser();

private:
  int id_;
  std::vector<std::string> users_;
  User user_;
};
