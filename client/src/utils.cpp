#include "utils.h"

/* std::vector<std::string> request_split(const std::string& data) {
  std::vector<std::string> elements;

  std::string element = "";

  bool special_block = false;

  for(auto it = data.begin(); it != data.end(); it++) {
    if (*it == '{' || *it == '}' || *it == '[' || *it == ']') {
      if (*it == '[' || *it == '{') {
        special_block = true;
      } else {
        special_block = false;
      }
    }

    if (*it == ',' && !special_block) {
      elements.push_back(element);
      element = "";
    } else {
      element += *it;
    }
  }

  return elements;
} */


std::vector<std::string> splitString(const std::string& data) {
    /* if (data.empty()) {
        throw std::runtime_error("Empty values in serialization");
    } */
    /* std::cout << data << std::endl;
     */
    std::vector<std::string> elements;

    std::string element = "";
    std::string tempStr(data);

    auto newEnd = std::remove_if(tempStr.begin(), tempStr.end(),
                                 [](char c)  { return separator.find(c) != std::string::npos; });
    tempStr.erase(newEnd, tempStr.end());

    for(auto it = tempStr.begin(); it != tempStr.end(); it++) {
        if ((*it == ':' || *it == ',') /* && !special_block */) {
            elements.push_back(element);
            element = "";
        } else {
            element += *it;
        }
    }
    elements.push_back(element);

    /* for (auto &i : elements) {
        std::cout << i << std::endl;
    } */

    return elements;
}


std::string boolToString(bool value) {
    return value ? "true" : "false";
}

bool stringToBool(const std::string value) {
    return (value == "true") ? true : false;
}

std::string serialize(const std::string &key, const std::vector<std::string> vec) {
    /* if (key.empty() || vec.empty()) {
        throw std::runtime_error("Empty values in serialization");
    } */
    
    std::string serialized = "\"" + key + "\": [ ";
    for (auto &v: vec) {
        serialized += "\"" + v + "\", ";
    }
    //serialized.erase(serialized.size() - 2, 1);
    serialized.pop_back();
    serialized.pop_back();
    serialized += " ] ";

    return serialized;
}

std::string serialize(const std::string &key, const std::string &value) {
    /* if (key.empty() || value.empty()) {
        throw std::runtime_error("Empty values in serialization");
    } */

    std::string serialized = "\"" + key + "\": \"" + value + "\",";
    return serialized;
}

std::string serialize(const std::string &key, const char* value) {
    if (key.empty()) {
        throw std::runtime_error("Empty values in serialization");
    }
    std::string serialized = "\"" + key + "\": \"" + std::string(value) + "\",";
    return serialized;
}

std::string serialize(const std::string &key, int value) {
    if (key.empty()) {
        throw std::runtime_error("Empty values in serialization");
    }
    std::string serialized = "\"" + key + "\": " + std::to_string(value) + ",";
    return serialized;
}

std::string serialize(const std::string &key, bool value) {
    if (key.empty()) {
        throw std::runtime_error("Empty values in serialization");
    }
    std::string serialized = "\"" + key + "\": " + boolToString(value) + ",";
    return serialized;
}




void fillData(const std::string& jsonStr, const std::string& key,  std::vector<std::string>* inputVec) {
    auto vec = splitString(jsonStr);
    for (auto it = std::find(vec.begin(), vec.end(), key) + 1; it !=  vec.end(); it++) {
        inputVec->push_back(*it);
    }
}



void fillData(const std::string& jsonStr, const std::string& key,  std::string* inputStr) {
    auto vec = splitString(jsonStr);

    auto it = std::find(vec.begin(), vec.end(), key) + 1;
    if (it != vec.end()) {
        *inputStr = *it;
    }
}


void fillData(const std::string& jsonStr, const std::string& key,  bool* val) {
    auto vec = splitString(jsonStr);

    auto it = std::find(vec.begin(), vec.end(), key) + 1;
    if (it != vec.end()) {
        *val = stringToBool((*it));
    }
}


/* void fillData(const std::string& jsonStr, const std::string& key,  int* val) {
    auto vec = request_split(jsonStr);
    for (auto &i : vec) {
        std::cout << i << std::endl;
    }

    auto it = std::find(vec.begin(), vec.end(), key) + 1;
    if (it != vec.end()) {
    std::cout << "AAAAAAAAAA" << std::endl;

        *val = atoi((*it).c_str());
    }
    

} */