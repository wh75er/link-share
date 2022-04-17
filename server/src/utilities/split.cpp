#include "utilities/split.hpp"

std::vector<std::string> request_split(std::string& data) {
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
}
