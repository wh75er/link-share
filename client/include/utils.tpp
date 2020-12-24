#pragma once



template<typename T, typename K, typename... Args>
std::string serializeData(T key, K value) {
    return serialize(key, value);
}

template<typename T, typename K, typename... Args>
std::string serializeData(T key, K value, Args... args) {
  return serialize(key, value) + serializeData(args...);
}


template<typename T, typename K, typename... Args>
std::string packToJsonString(T key, K value, Args... args) {
    std::string jsonStr("");
    jsonStr = "{";
    jsonStr += serializeData(key, value, args...);
    jsonStr += "}"; 
    return jsonStr;
}



// Все, что связано с распаковкой JSON'а



template<typename T, typename K, typename... Args>
void fillDataFromJson(const std::string& jsonStr, const T& key, K* inputVal) {
    fillData(jsonStr, key, inputVal);
}

template<typename T, typename K, typename... Args>
void fillDataFromJson(const std::string& jsonStr, const T& key, K* inputVal, Args... args) {
    fillData(jsonStr, key, inputVal);
    fillDataFromJson(jsonStr, args...);
}

