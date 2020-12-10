#pragma once
#include <string>


class UserInfo{
public:
    UserInfo();
    UserInfo(std::string nm, std::string psw);
    ~UserInfo();

private:
    std::string name;
    std::string password;
};