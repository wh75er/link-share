#pragma once
#include <string>


class UserInfo{
public:
    UserInfo();
    UserInfo(std::string name, std::string password, std::string uuid);
    std::string getInfoStr();
    void setUserInfo(const std::string& str);
    ~UserInfo();

private:
    std::string name;
    std::string password;
    std::string uuid;
};