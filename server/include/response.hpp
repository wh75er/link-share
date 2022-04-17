#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

class Response {
public:
  class Builder;

  Response() = default;
  explicit Response(std::string _error, std::string _uuid, std::vector<std::map<std::string, std::string>> _objects, std::string files_dir);
  ~Response() = default;

  std::string serialize();

  std::string error;
  std::string uuid;
  std::vector<std::map<std::string, std::string>> objects;
  std::string files_dir;
};

class Response::Builder {
public:
  Builder& error(std::string& error);
  Builder& uuid(std::string& uuid);
  Builder& objects(std::vector<std::map<std::string, std::string>>& objects);
  Builder& files_dir(std::string& files_dir);
  Response build() const;

private:
  std::string _error;
  std::string _uuid;
  std::vector<std::map<std::string, std::string>> _objects;
  std::string _files_dir;
};
