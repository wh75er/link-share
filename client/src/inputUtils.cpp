#include "inputUtils.hpp"
#include "utils.h"
#include <iostream>

void fillObject(std::string *str)
{
    //std::cin >> *str;
    char c = 'a';
    while ((c = getchar()) != '\n')
    {
        //c = getchar();
        //std::cout << "Char = " << c << '\n';
        (*str).push_back(c);
    }
    //std::cout << "String = " <<  (*str) << '\n';
    
}
void fillObject(std::vector<std::string> *vec)
{
    size_t amount = 0;
    std::string newObj;
    std::cin >> amount;
    while (amount > 0)
    {
        //std::getline(std::cin, newObj/* , '\n' */);
        //std::cout << newObj << std::endl;
        char c = 'a';
        while ((c = getchar()) != '\n')
        {
            // = getchar();
            newObj.push_back(c);
        }
        //std::cin.getline(*str);
        //std::cin >> newObj;
        vec->push_back(newObj);
        --amount;
    }
}

/* std::string createRoomInput() {
    std::string name;
    std::string isPrivate;

    writeData(&name, &isPrivate);

    std::string ret = packToJsonString("command", "0", "name", name, "private", isPrivate);
    return ret;
} */

/* std::string deleteRoomInput() {
    std::string name;
    std::string host;

    writeData(&name, &host);
    
    std::string ret = packToJsonString("command","1", "name", name, "host", host);
    return ret;
} */

/* std::string addUsersInput() {
    std::vector<std::string> vec;
    writeData(&vec);

    std::string ret = packToJsonString("command","2", "users", vec);
    return ret;
} */

/* std::string deleteUsersInput() {
    std::vector<std::string> vec;
    writeData(&vec);

    std::string ret = packToJsonString("command","3", "users", vec);
    return ret;
} */
std::string addLinkInput()
{
    std::string name;
    std::string url;
    std::string description;

    writeData(&name, &url, &description);

    std::string ret = packToJsonString("command", "4", "name", name, "url", url, "description", description);
    return ret;
}
std::string deleteLinkInput()
{
    std::string name;

    writeData(&name);

    std::string ret = packToJsonString("command", "5", "name", name);
    return ret;
}
std::string makeSnapshotInput()
{
    std::string name;

    writeData(&name);

    std::string ret = packToJsonString("command", "6", "name", name);
    return ret;
}
std::string logInInput()
{
    std::string login;
    std::string password;

    writeData(&login, &password);

    std::string ret = packToJsonString("command", "7", "login", login, "password", password);
    return ret;
}
std::string signUpInput()
{
    std::string login;
    std::string password;

    writeData(&login, &password);

    std::string ret = packToJsonString("command", "8", "login", login, "password", password);
    return ret;
}

std::string downloadSnapshotInput()
{
    std::string uuid, filesdir;

    writeData(&uuid, &filesdir);

    std::string ret = packToJsonString("command", "9", "uuid", uuid,  "filesdir", filesdir);
    return ret;
}

std::string getUserRoomInput()
{
    std::string ret = packToJsonString("command", "10");
    return ret;
}

std::string getUserLinksInput()
{
    std::string ret = packToJsonString("command", "11");
    return ret;
}

std::string getLinkSnapshotsInput()
{
    std::string name;

    writeData(&name);
    std::string ret = packToJsonString("command", "12", "name", name);
    return ret;
}
