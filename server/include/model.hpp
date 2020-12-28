#pragma once

#include <map>
#include <cstdlib>

#include "create_new_page.hpp"
#include "dbModel.hpp"

#define SNAPSHOTS_DIR "snapshots"

template<class DbOps, class Uuid>
class Model {
public:
  explicit Model(std::shared_ptr<DbOps> dbops);
  ~Model() = default;

  bool identify(std::string& login, std::string& token);

  std::map<std::string, bool> get_user_room_ownership(std::string& login, std::string room_uuid);

  std::string generate_token(std::string& login, std::string& password);

  std::string create_room(std::string& login, std::string& name, bool private_);

  std::string create_link(std::string& login, std::string& url, std::string& name, std::string& description, std::string& room_uuid);

  std::string create_snapshot(std::string& login, std::string& link_uuid);

  std::string get_snapshot(std::string& login, std::string& snapshot_uuid);

  std::string get_room_for_user(std::string& login);

  std::vector<std::map<std::string, std::string>> get_room_links(std::string& room_uuid);

  void delete_snapshot(std::string& snapshot_uuid);

  void delete_room(std::string& login, std::string& room_uuid);

  void delete_link(std::string& link_uuid);

  void delete_link(std::string& login, std::string& link_uuid);

  void add_users(std::vector<std::string>& users, std::string& room_uuid);

  void delete_users(std::string& login, std::vector<std::string>& users, std::string& room_uuid);

  void sign_up_user(std::string& login, std::string& password);

private:
  Uuid uuid;
  DbApi<DbOps> api{};
};

template<class DbOps, class Uuid>
Model<DbOps, Uuid>::Model(std::shared_ptr <DbOps> dbops):
        api(DbApi(dbops)) {
}

template<class DbOps, class Uuid>
bool Model<DbOps, Uuid>::identify(std::string& login, std::string& token) {
  std::map<std::string, std::string> user;

  try {
    user = api.get_user_by_login(login);
  }
  catch (...) {
    throw;
  }

  return user["token"] == token;
}

template<class DbOps, class Uuid>
std::map<std::string, bool> Model<DbOps, Uuid>::get_user_room_ownership(std::string& login, std::string room_uuid) {
  std::map<std::string, bool> ownership;

  ownership["is_owner"] = false;
  ownership["is_participant"] = false;

  std::map<std::string, std::string> user;
  try {
    user = api.get_user_by_login(login);
  }
  catch (...) {
    throw;
  }

  std::map<std::string, std::string> room;
  try {
    room = api.get_room_by_uuid(room_uuid);
  }
  catch (...) {
    throw;
  }

  if (user["id"].empty() || room["user_id"].empty()) {
    throw std::runtime_error("Failed to get entities fields!");
  }

  std::vector<std::map<std::string, std::string>> room_users;
  try {
    room_users = api.get_room_users_by_uuid(room_uuid);
  }
  catch (...) {
    throw;
  }

  bool is_owner = user["id"] == room["user_id"];
  bool is_participant = false;
  for (auto& room_user : room_users) {
    if (room_user["id"].empty()) {
      throw std::runtime_error("Failed to get entity field!");
    }

    if (room_user["id"] == user["id"]) {
      is_participant = true;
      break;
    }
  }

  ownership["is_owner"] = is_owner;
  ownership["is_participant"] = is_participant;

  return ownership;
}

template<class DbOps, class Uuid>
std::string Model<DbOps, Uuid>::generate_token(std::string &login, std::string &password) {
  std::map<std::string, std::string> user;

  try {
    user = api.get_user_by_login(login);
  }
  catch (...) {
    throw;
  }

  if (user["password"] != password) {
    throw std::runtime_error("User not found or password is incorrect!");
  }

  uuid.generate();

  std::string user_token = uuid.to_string();

  try {
    api.set_user_token(login, user_token);
  }
  catch (...) {
    throw;
  }

  return user_token;
};

template<class DbOps, class Uuid>
std::string Model<DbOps, Uuid>::create_room(std::string &login, std::string &name, bool private_) {
  uuid.generate();

  std::string room_uuid = uuid.to_string();

  try {
    api.add_room(login, name, private_, room_uuid);
  }
  catch (...) {
    throw;
  }

  return room_uuid;
}

template<class DbOps, class Uuid>
std::string Model<DbOps, Uuid>::create_link(std::string& login, std::string &url, std::string &name, std::string &description,
                                            std::string &room_uuid) {
  std::map<std::string, bool> ownership;
  try {
    ownership = get_user_room_ownership(login, room_uuid);
  }
  catch (...) {
    throw;
  }

  if (!ownership["is_owner"] && !ownership["is_participant"]) {
    throw std::runtime_error("User is not allowed to create links in the room!");
  }

  uuid.generate();

  std::string link_uuid = uuid.to_string();

  try {
    api.add_link_to_room(url, name, description, link_uuid, room_uuid);
  }
  catch (...) {
    throw;
  }

  return link_uuid;
}

template<class DbOps, class Uuid>
std::string Model<DbOps, Uuid>::create_snapshot(std::string& login, std::string &link_uuid) {
  std::map<std::string, std::string> room;
  try {
    room = api.get_room_by_link_uuid(link_uuid);
  }
  catch (...) {
    throw;
  }

  std::map<std::string, bool> ownership;
  try {
    ownership = get_user_room_ownership(login, room["room_uuid"]);
  }
  catch (...) {
    throw;
  }

  if (!ownership["is_owner"] && !ownership["is_participant"]) {
    throw std::runtime_error("User is not allowed to create snapshots for links in that room!");
  }

  uuid.generate();

  std::string snapshot_uuid = uuid.to_string();

  std::map<std::string, std::string> link;
  try {
    link = api.get_link_by_uuid(link_uuid);
  }
  catch (...) {
    throw;
  }

  const char* snapshot_dir = std::getenv("SNAPSHOTS_DIR");
  std::string directory;
  if (snapshot_dir) {
    directory = std::string(snapshot_dir) + "/" + snapshot_uuid;
  } else {
    directory = std::string(SNAPSHOTS_DIR) + "/" + snapshot_uuid;
  }

  // Use library to get all the specified files
  try {
    create_new_page(link["url"], directory);
  }
  catch (...) {
    throw;
  }

  try {
    api.add_snapshot_to_link(snapshot_uuid, directory, link_uuid);
  }
  catch (...) {
    throw;
  }

  return snapshot_uuid;
}

template<class DbOps, class Uuid>
std::string Model<DbOps, Uuid>::get_snapshot(std::string& login, std::string& snapshot_uuid) {
  std::map<std::string, std::string> snapshot;
  try {
    snapshot = api.get_snapshot_by_uuid(snapshot_uuid);
  }
  catch (...) {
    throw;
  }

  if (snapshot.empty()) {
    throw std::runtime_error("Snapshot not found!");
  }

  return snapshot["dir_name"];
}

template<class DbOps, class Uuid>
std::string Model<DbOps, Uuid>::get_room_for_user(std::string& login) {
  std::vector<std::map<std::string, std::string>> user_rooms;
  try {
    user_rooms = api.get_all_user_rooms(login);
  }
  catch (...) {
    throw;
  }


  std::string room_uuid;
  if (user_rooms.empty()) {
    uuid.generate();
    room_uuid = uuid.to_string();

    try {
      std::string room_name("room");
      api.add_room(login, room_name, true, room_uuid);
    }
    catch (...) {

    }
  } else {
    room_uuid = user_rooms[0]["room_uuid"];
  }

  return room_uuid;
}

template<class DbOps, class Uuid>
std::vector<std::map<std::string, std::string>> Model<DbOps, Uuid>::get_room_links(std::string& room_uuid) {
  std::vector<std::map<std::string, std::string>> room_links;
  try {
    room_links = api.get_room_links_by_uuid(room_uuid);
  }
  catch (...) {
    throw;
  }

  return room_links;
}

template<class DbOps, class Uuid>
void Model<DbOps, Uuid>::delete_room(std::string& login, std::string &room_uuid) {
  std::map<std::string, bool> ownership;
  try {
    ownership = get_user_room_ownership(login, room_uuid);
  }
  catch (...) {
    throw;
  }

  if (!ownership["is_owner"]) {
    throw std::runtime_error("User is not allowed to delete room!");
  }

  try {
    std::vector<std::map<std::string, std::string>> links;

    links = api.get_room_links_by_uuid(room_uuid);

    api.delete_users_from_room(room_uuid);
    api.delete_links_from_room(room_uuid);
    api.delete_room(room_uuid);

    for (auto &link : links) {
      delete_link(link["link_uuid"]);
    }
  }
  catch (...) {
    throw;
  }
}

template<class DbOps, class Uuid>
void Model<DbOps, Uuid>::delete_snapshot(std::string &snapshot_uuid) {
  try {
    api.delete_snapshot(snapshot_uuid);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps, class Uuid>
void Model<DbOps, Uuid>::delete_link(std::string &link_uuid) {
  try {
    std::vector<std::map<std::string, std::string>> snapshots;
    snapshots = api.get_link_snapshots_by_uuid(link_uuid);

    for (auto &snapshot: snapshots) {
      delete_snapshot(snapshot["snapshot_uuid"]);
    }

    api.delete_link_comments(link_uuid);
    api.delete_link(link_uuid);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps, class Uuid>
void Model<DbOps, Uuid>::delete_link(std::string& login, std::string& link_uuid) {
  std::map<std::string, std::string> room;
  try {
    room = api.get_room_by_link_uuid(link_uuid);
  }
  catch (...) {
    throw;
  }

  std::map<std::string, bool> ownership;
  try {
    ownership = get_user_room_ownership(login, room["room_uuid"]);
  }
  catch (...) {
    throw;
  }

  if (!ownership["is_owner"] && !ownership["is_participant"]) {
    throw std::runtime_error("User is not allowed to delete links in the room!");
  }

  try {
    std::vector<std::map<std::string, std::string>> snapshots;
    snapshots = api.get_link_snapshots_by_uuid(link_uuid);

    for (auto &snapshot: snapshots) {
      delete_snapshot(snapshot["snapshot_uuid"]);
    }

    api.delete_link_comments(link_uuid);
    api.delete_link(link_uuid);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps, class Uuid>
void Model<DbOps, Uuid>::add_users(std::vector<std::string> &users, std::string &room_uuid) {
  try {
    for (auto& user : users) {
      api.get_user_by_login(user);
    }

    api.add_users_to_room(users, room_uuid);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps, class Uuid>
void Model<DbOps, Uuid>::delete_users(std::string& login, std::vector<std::string> &users, std::string &room_uuid) {
  std::map<std::string, bool> ownership;
  try {
    ownership = get_user_room_ownership(login, room_uuid);
  }
  catch (...) {
    throw;
  }

  if (!ownership["is_owner"]) {
    throw std::runtime_error("User is not allowed to delete other users from room!");
  }

  try {
    for (auto& user : users) {
      api.get_user_by_login(user);
    }

    api.delete_users_from_room(users, room_uuid);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps, class Uuid>
void Model<DbOps, Uuid>::sign_up_user(std::string& login, std::string& password) {
  try {
    api.add_user(login, password);
  }
  catch (...) {
    throw;
  }
}
