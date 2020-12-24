#include "userinfo.hpp"
#include "utils.h"
#include <stdexcept>

UserInfo::UserInfo() : name("default"), password("default"), uuid("default") {}
UserInfo::UserInfo(std::string name, std::string password, std::string uuid) 
: name(std::move(name)),
  password(std::move(password)),
  uuid(std::move(uuid)) {
}

std::string UserInfo::getInfoStr() {
    /* if (name.empty() || name.empty() || name.empty()) {
        throw std::runtime_error("User info is empty!");
    } */

    std::string ret = packToJsonString("name", name, "password", password, "uuid", uuid);
    return ret;
}

void UserInfo::setUserInfo(const std::string& str) {
    if (str.empty()) {
        throw std::runtime_error("User info is empty!");
    }
    fillDataFromJson(str, "name", &name, "password", &password, "uuid", &uuid);
}


UserInfo::~UserInfo() {}
