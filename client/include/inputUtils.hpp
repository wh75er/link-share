#pragma once
#include <string>
#include <vector>

template<typename T, typename... Args>
void writeData(T* key);

template<typename T, typename... Args>
void writeData(T* key, Args... args);

void fillObject(std::string* str);
void fillObject(std::vector<std::string>* str);


std::string createRoomInput();
std::string deleteRoomInput();
std::string addUsersInput();
std::string deleteUsersInput();
std::string addLinkInput();
std::string deleteLinkInput();
std::string makeSnapshotInput();
std::string logInInput();
std::string signUpInput();

#include "inputUtils.tpp"