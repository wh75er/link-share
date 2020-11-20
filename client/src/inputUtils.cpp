#include "inputUtils.hpp"
#include "utils.h"

void fillObject(std::string* str) {
    std::cin >> *str;
}
void fillObject(std::vector<std::string>* vec) {
    size_t amount = 0;
    std::string newObj;
    std::cin >> amount;
        while(amount > 0) {
            std::cin >> newObj;
            vec->push_back(newObj);
            --amount;
        }
}


std::string createRoomInput() {
    std::string name;
    std::string host;

    writeData(&name, &host);

    std::string ret = packToJsonString("command", "0", "name", name, "host", host);
    return ret;
}

std::string deleteRoomInput() {
    std::string name;
    std::string host;

    writeData(&name, &host);
    
    std::string ret = packToJsonString("command","1", "name", name, "host", host);
    return ret;
}

std::string addUsersInput() {
    std::vector<std::string> vec;
    writeData(&vec);

    std::string ret = packToJsonString("command","2", "users", vec);
    return ret;
}

std::string deleteUsersInput() {
    std::vector<std::string> vec;
    writeData(&vec);

    std::string ret = packToJsonString("command","3", "users", vec);
    return ret;
}
std::string addLinkInput() {
    std::string name;
    std::string url;

    writeData(&name, &url);
    
    std::string ret = packToJsonString("command","4", "name", name, "url", url);
    return ret;
}
std::string deleteLinkInput() {
    std::string name;

    writeData(&name);
    
    std::string ret = packToJsonString("command","5", "name", name);
    return ret;
}
std::string makeSnapshotInput() {
    std::string name;

    writeData(&name);
    
    std::string ret = packToJsonString("command","6", "name", name);
    return ret;
}
std::string logInInput() {
    std::string login;
    std::string password;

    writeData(&login, &password);
    
    std::string ret = packToJsonString("command","7", "login", login, "password", password);
    return ret;
}
std::string signUpInput() {
    std::string login;
    std::string password;

    writeData(&login, &password);
    
    std::string ret = packToJsonString("command","8", "login", login, "password", password);
    return ret;
}