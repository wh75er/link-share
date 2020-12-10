#include "userinfo.hpp"

UserInfo::UserInfo() : name(""), password("") {}
UserInfo::UserInfo(std::string nm, std::string psw) : name(std::move(nm)), password(std::move(psw)){
}
UserInfo::~UserInfo() {}
