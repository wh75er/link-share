#pragma once

#include <string>

class User {
public:
  User();
  User(std::string name, std::string token, int roomId);
  User(std::string name, std::string password, std::string token, int roomId);
  ~User() {};

  void setName(std::string name);
  void setPassword(std::string password);
  void setToken(std::string token);
  void setRoomId(int roomId);

  std::string getName();
  std::string getPassword();
  std::string getToken();
  int getRoomId();

private:
  std::string name_;
  std::string password_;
  std::string token_;
  int roomId_;
};
