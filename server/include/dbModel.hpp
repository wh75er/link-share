#pragma once

#include <map>

template<class DbOps>
class DbApi {
public:
  explicit DbApi(std::shared_ptr<DbOps> dbops_):
          dbops(dbops_) {
  }

  ~DbApi() = default;

  std::map<std::string, std::string> get_user_by_login(std::string& login);
  std::map<std::string, std::string> get_room_by_uuid(std::string& uuid);
  std::map<std::string, std::string> get_room_by_link_uuid(std::string& uuid);
  std::map<std::string, std::string> get_link_by_uuid(std::string& uuid);
  std::map<std::string, std::string> get_snapshot_by_uuid(std::string& uuid);
  std::map<std::string, std::string> get_comment_by_uuid(std::string& uuid);

  std::vector<std::map<std::string, std::string>> get_room_users_by_uuid(std::string& uuid);
  std::vector<std::map<std::string, std::string>> get_room_links_by_uuid(std::string& uuid);
  std::vector<std::map<std::string, std::string>> get_link_snapshots_by_uuid(std::string& uuid);
  std::vector<std::map<std::string, std::string>> get_link_comments_by_uuid(std::string& uuid);

  void add_user(std::string& login, std::string& password);
  void add_room(std::string& login, std::string& name, bool private_, std::string& uuid);
  void add_link_to_room(std::string& url, std::string& name, std::string& description, std::string& link_uuid, std::string& room_uuid);
  void add_users_to_room(std::vector<std::string>& users, std::string& room_uuid);
  void add_comment_to_link(std::string& comment_uuid, std::string& content, std::string& link_uuid);
  void add_snapshot_to_link(std::string& snapshot_uuid, std::string& dir_name, std::string& link_uuid);

  void set_user_token(std::string& login, std::string& token);

  void delete_room(std::string& room_uuid);
  void delete_link(std::string& link_uuid);
  void delete_link_from_room(std::string& link_uuid, std::string& room_uuid);
  void delete_links_from_room(std::string& room_uuid);
  void delete_users_from_room(std::vector<std::string>& users, std::string& room_uuid);
  void delete_users_from_room(std::string& room_uuid);
  void delete_comment(std::string& comment_uuid);
  void delete_snapshot(std::string& snapshot_uuid);
  void delete_link_snapshots(std::string& link_uuid);
  void delete_link_comments(std::string& link_uuid);

private:
  std::shared_ptr<DbOps> dbops = nullptr;
};

template<class DbOps>
std::map<std::string, std::string> DbApi<DbOps>::get_user_by_login(std::string &login) {
  std::string query = "SELECT * FROM users where login='" + login + "';";

  std::map<std::string, std::string> row;

  try {
    row = dbops->get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

template<class DbOps>
std::map<std::string, std::string> DbApi<DbOps>::get_room_by_uuid(std::string& uuid) {
  std::string query = "SELECT * FROM rooms where room_uuid='" + uuid + "';";

  std::map<std::string, std::string> row;

  try {
    row = dbops->get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

template<class DbOps>
std::map<std::string, std::string> DbApi<DbOps>::get_room_by_link_uuid(std::string& uuid) {
  std::string query = "select * from rooms where id=(select room_id from room_links where link_id=(select * from web_links where link_uuid='" + uuid + "'));";

  std::map<std::string, std::string> row;

  try {
    row = dbops->get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

template<class DbOps>
std::map<std::string, std::string> DbApi<DbOps>::get_link_by_uuid(std::string &uuid) {
  std::string query = "SELECT * FROM link where link_uuid='" + uuid + "';";

  std::map<std::string, std::string> row;

  try {
    row = dbops->get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

template<class DbOps>
std::map<std::string, std::string> DbApi<DbOps>::get_snapshot_by_uuid(std::string &uuid) {
  std::string query = "SELECT * FROM snapshots where snapshot_uuid='" + uuid + "';";

  std::map<std::string, std::string> row;

  try {
    row = dbops->get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

template<class DbOps>
std::map<std::string, std::string> DbApi<DbOps>::get_comment_by_uuid(std::string &uuid) {
  std::string query = "SELECT * FROM comments where comment_uuid='" + uuid + "';";

  std::map<std::string, std::string> row;

  try {
    row = dbops->get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

template<class DbOps>
std::vector<std::map<std::string, std::string>> DbApi<DbOps>::get_room_users_by_uuid(std::string &uuid) {
  std::string query = "select * from users where id in "
                      "(select user_id from room_users where room_id="
                      "(select id from rooms where room_uuid='" + uuid + "'));";

  std::vector<std::map<std::string, std::string>> rows;

  try {
    rows = dbops->get_rows_by_query(query);
  }
  catch (...) {
    throw;
  }

  return rows;
}

template<class DbOps>
std::vector<std::map<std::string, std::string>> DbApi<DbOps>::get_room_links_by_uuid(std::string &uuid) {
  std::string query = "select * from web_links where id in "
                      "(select link_id from room_links where room_id="
                      "(select id from rooms where room_uuid='" + uuid + "'))";

  std::vector<std::map<std::string, std::string>> rows;

  try {
    rows = dbops->get_rows_by_query(query);
  }
  catch (...) {
    throw;
  }

  return rows;
}

template<class DbOps>
std::vector<std::map<std::string, std::string>> DbApi<DbOps>::get_link_snapshots_by_uuid(std::string &uuid) {
  std::string query = "select * from snapshots where link_id in "
                      "(select id from web_links where link_uuid='" + uuid + "');";

  std::vector<std::map<std::string, std::string>> rows;

  try {
    rows = dbops->get_rows_by_query(query);
  }
  catch (...) {
    throw;
  }

  return rows;
}

template<class DbOps>
std::vector<std::map<std::string, std::string>> DbApi<DbOps>::get_link_comments_by_uuid(std::string &uuid) {
  std::string query = "select * from comments where link_id in "
                      "(select id from web_links where link_uuid='" + uuid + "');";

  std::vector<std::map<std::string, std::string>> rows;

  try {
    rows = dbops->get_rows_by_query(query);
  }
  catch (...) {
    throw;
  }

  return rows;
}

template<class DbOps>
void DbApi<DbOps>::add_user(std::string &login, std::string &password) {
  std::string query = "insert into users (login, password) values ('" + login + "', '" + password + "');";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::add_room(std::string& login, std::string& name, bool private_, std::string &uuid) {
  std::string boolean = private_ ? "true" : "false";
  std::string query = "insert into rooms (room_uuid, name, private, room_date, user_id) values "
                      "('" + uuid + "', " + name + ", " + boolean + ", NOW(), (select id from users where login='" + login + "'));";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::add_link_to_room(std::string& url, std::string& name, std::string& description, std::string& link_uuid, std::string& room_uuid) {
  std::string query1 = "insert into web_links (url, name, description, link_date, link_uuid) values "
                       "('" + url + "', '" + name + "', '" + description + "', NOW(), '" + link_uuid + "');";

  std::string query2 = "insert into room_links (room_id, link_id) values "
                       "((select id from rooms where room_uuid='" + room_uuid + "'), "
                                                                                "(select id from links where link_uuid='" + link_uuid + "'));";

  try {
    dbops->exec_query_command(query1);
    dbops->exec_query_command(query2);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::add_users_to_room(std::vector<std::string> &users, std::string &room_uuid) {
  for (auto i = 0; i < users.size(); i++) {
    std::string query = "insert into room_users (room_id, user_id) values "
                        "((select id from rooms where room_uuid='" + room_uuid + "'), "
                                                                                 "(select id from users where login='" + users[i] + "'));";

    try {
      dbops->exec_query_command(query);
    }
    catch (...) {
      throw;
    }
  }
}

template<class DbOps>
void DbApi<DbOps>::add_comment_to_link(std::string& comment_uuid, std::string& content, std::string &link_uuid) {
  std::string query = "insert into comments (comment_uuid, content, link_id) values "
                      "('" + comment_uuid + "', '" + content + "', "
                                                               "(select id from web_links where link_uuid='" + link_uuid + "'));";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::add_snapshot_to_link(std::string& snapshot_uuid, std::string& dir_name, std::string& link_uuid) {
  std::string query = "insert into snapshots (snapshot_uuid, dir_name, link_id, snapshot_date) values "
                      "('" + snapshot_uuid + "', '" + dir_name + "', "
                                                                 "(select id from web_links where link_uuid='" + link_uuid + "'), "
                                                                                                                             "NOW());";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::set_user_token(std::string &login, std::string &token) {
  std::string query = "update users set token = '" + token + "', date = NOW() where login = '" + login + "';";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::delete_room(std::string &room_uuid) {
  std::string query = "delete from rooms where room_uuid='" + room_uuid + "';";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::delete_link(std::string &link_uuid) {
  std::string query = "delete from web_links where link_uuid='" + link_uuid + "';";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::delete_link_from_room(std::string &link_uuid, std::string &room_uuid) {
  std::string query = "delete from room_links where link_id=(select id from web_links where link_uuid='" + link_uuid + "') and "
                                                                                                                       "room_id=(select id from rooms where room_uuid='" + room_uuid + "');";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::delete_links_from_room(std::string &room_uuid) {
  std::string query = "delete from room_links where room_id=(select id from rooms where room_uuid='" + room_uuid + "');";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::delete_users_from_room(std::vector<std::string>& users, std::string& room_uuid) {
  for (auto i = 0; i < users.size(); i++) {
    std::string query = "delete from room_users where user_id=(select id from users where login='" + users[i] +"') and "
                                                                                                               "room_id=(select id from rooms where room_uuid='" + room_uuid + "');";
    try {
      dbops->exec_query_command(query);
    }
    catch (...) {
      throw;
    }
  }
}

template<class DbOps>
void DbApi<DbOps>::delete_users_from_room(std::string &room_uuid) {
  std::string query = "delete from room_users where room_id=(select id from rooms where room_uuid='" + room_uuid + "');";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::delete_comment(std::string &comment_uuid) {
  std::string query = "delete from comments where comment_uuid='" + comment_uuid + "';";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::delete_snapshot(std::string &snapshot_uuid) {
  std::string query = "delete from snapshots where snapshot_uuid='" + snapshot_uuid + "';";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::delete_link_snapshots(std::string &link_uuid) {
  std::string query = "delete from snapshots where link_id=(select id from web_links where link_uuid='" + link_uuid + "');";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

template<class DbOps>
void DbApi<DbOps>::delete_link_comments(std::string &link_uuid) {
  std::string query = "delete from comments where link_id=(select id from web_links where link_uuid='" + link_uuid + "');";

  try {
    dbops->exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}
