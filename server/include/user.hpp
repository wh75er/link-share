#pragma once

#include <string>

class User {
public:
  User();
  User(std::string name, std::string token, int roomId);
  ~User() {};

  void setName(std::string name);
  void setToken(std::string token);
  void setRoomId(int roomId);

  std::string getName();
  std::string getToken();
  int getRoomId();

private:
  std::string name_;
  std::string token_;
  int roomId_;
};
