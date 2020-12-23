#pragma once

#include <map>

#include "dbModel.hpp"

#define SNAPSHOTS_DIR "snapshots"

template<class DbOps, class Uuid>
class Model {
public:
  explicit Model(std::shared_ptr<DbOps> dbops);
  ~Model() = default;

  bool identify(std::string& login, std::string& token);

  std::string generate_token(std::string& login, std::string& password);

  std::string create_room(std::string& login, std::string& name, bool private_);

  std::string create_link(std::string& url, std::string& name, std::string& description, std::string& room_uuid);

  std::string create_snapshot(std::string& link_uuid);

  void delete_snapshot(std::string& snapshot_uuid);

  void delete_room(std::string& room_uuid);

  void delete_link(std::string& link_uuid);

  void add_users(std::vector<std::string>& users, std::string& room_uuid);

  void delete_users(std::vector<std::string>& users, std::string& room_uuid);

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
std::string Model<DbOps, Uuid>::generate_token(std::string &login, std::string &password) {
  std::map<std::string, std::string> user;

  try {
    user = api.get_user_by_login(login);
  }
  catch (...) {
    throw;
  }

  if (user["password"] != password) {
    throw std::runtime_error("User not found or password is incorect!");
  }

  uuid.generate();

  std::string user_token = uuid.to_string();

  api.set_user_token(login, user_token);

  return user_token;
};

template<class DbOps, class Uuid>
std::string Model<DbOps, Uuid>::create_room(std::string &login, std::string &name, bool private_) {
  uuid.generate();

  std::string room_token = uuid.to_string();

  try {
    api.add_room(login, name, private_, room_token);
  }
  catch (...) {
    throw;
  }

  return room_token;
}

template<class DbOps, class Uuid>
std::string Model<DbOps, Uuid>::create_link(std::string &url, std::string &name, std::string &description,
                                            std::string &room_uuid) {
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
std::string Model<DbOps, Uuid>::create_snapshot(std::string &link_uuid) {
  uuid.generate();

  std::string snapshot_uuid = uuid.to_string();

  std::string directory = std::string(SNAPSHOTS_DIR) + "/" + uuid;
  try {
    api.add_snapshot_to_link(snapshot_uuid, directory, link_uuid);
  }
  catch (...) {
    throw;
  }

  return snapshot_uuid;
}

template<class DbOps, class Uuid>
void Model<DbOps, Uuid>::delete_room(std::string &room_uuid) {
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
void Model<DbOps, Uuid>::delete_users(std::vector<std::string> &users, std::string &room_uuid) {
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