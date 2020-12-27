#include "response.hpp"

Response::Response(std::string _error, std::string _uuid, std::vector<std::map<std::string, std::string>> _objects,
                     std::string _files_dir):
  error(_error),
  uuid(_uuid),
  objects(_objects),
  files_dir(_files_dir)
{
}

std::string Response::serialize() {
  std::string json = "{";

  error.erase(std::remove(error.begin(), error.end(), '\''), error.end());
  error.erase(std::remove(error.begin(), error.end(), '\"'), error.end());

  std::string json_error = "\"error\": " + std::string("\"") + error + std::string("\"");

  json += json_error;

  if (!uuid.empty()) {
    std::string json_uuid = "\"uuid\": " + std::string("\"") + uuid + std::string("\"");
    json += ", " + json_uuid;
  }

  if (!objects.empty()) {
    std::string json_objects = "\"objects\": ";
    std::string json_objects_array = "[";
    for (auto& object : objects) {
      std::string json_object = "{";
      for (auto& field : object) {
        json_object += std::string("\"") + field.first + std::string("\"");
        json_object += std::string(": ") + std::string("\"") + field.second + std::string("\"");
        json_object += std::string(",");
      }
      json_object.pop_back();
      json_object += "}";
      json_objects_array += json_object + ", ";
    }
    json_objects_array.pop_back();
    json_objects_array += "]";

    json_objects += json_objects_array;

    json += ", " + json_objects;
  }

  if (!files_dir.empty()) {
    std::string json_uuid = "'files_dir': " + std::string("\"") + files_dir + std::string("\"");
    json += ", " + json_uuid;
  }

  json += "}";

  return json;
}


Response::Builder& Response::Builder::error(std::string& error) {
  _error = error;
  return *this;
}

Response::Builder& Response::Builder::uuid(std::string& uuid) {
  _uuid = uuid;
  return *this;
}

Response::Builder& Response::Builder::objects(std::vector<std::map<std::string, std::string>>& objects) {
  _objects = objects;
  return *this;
}

Response::Builder& Response::Builder::files_dir(std::string& files_dir) {
  _files_dir = files_dir;
  return *this;
}

Response Response::Builder::build() const {
  return Response(_error,
                  _uuid,
                  _objects,
                  _files_dir);
}
