#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

const std::string separator  = "{}[]\" ";


// Все, что связано с сериализацией в JSON

std::vector<std::string> request_split(const std::string& data);

std::vector<std::string> splitString(std::string& data);


std::string boolToString(bool value);

std::string serialize(const std::string &key, const std::vector<std::string> vec);

std::string serialize(const std::string &key, const std::string &value);

std::string serialize(const std::string &key, int value);

std::string serialize(const std::string &key, bool value);

template<typename T, typename K, typename... Args>
std::string serializeData(T key, K value);

template<typename T, typename K, typename... Args>
std::string serializeData(T key, K value, Args... args);

template<typename T, typename K, typename... Args>
std::string packToJsonString(T key, K value, Args... args);



// Все, что связано с распаковкой JSON'а


void fillData(const std::string& jsonStr, const std::string& key,  std::vector<std::string>* inputVec);

void fillData(const std::string& jsonStr, const std::string& key,  std::string* inputStr);

template<typename T, typename K, typename... Args>
void fillDataFromJson(const std::string& jsonStr, const T& key, K* inputVal);

template<typename T, typename K, typename... Args>
void fillDataFromJson(const std::string& jsonStr, const T& key, K* inputVal, Args... args);

#include "utils.tpp"