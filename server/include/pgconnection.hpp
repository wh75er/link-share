#pragma once

#include <memory>
#include <mutex>
#include <libpq-fe.h>
#include <string>
#include <queue>
#include <condition_variable>
#include <thread>
#include <map>
#include <vector>
#include <stdexcept>

class PGConnection {
public:
  PGConnection();
  [[nodiscard]] std::shared_ptr<PGconn> connection() const;

private:
  std::string m_dbhost = "localhost";
  int         m_dbport = 5432;
  std::string m_dbname = "link-share";
  std::string m_dbuser = "postgres";
  std::string m_dbpass = "postgres";

  std::shared_ptr<PGconn>  m_connection;

};


class PGBackend {
public:
  PGBackend();
  std::shared_ptr<PGConnection> connection();
  void freeConnection(std::shared_ptr<PGConnection>);

private:
  void createPool();

  std::mutex m_mutex;
  std::condition_variable m_condition;
  std::queue<std::shared_ptr<PGConnection>> m_pool;

  const uint POOL = std::thread::hardware_concurrency();
};


class DbOps {
public:
  DbOps() = default;
  ~DbOps() = default;

  std::map<std::string, std::string> get_user_by_login(std::string& login);
  std::map<std::string, std::string> get_room_by_uuid(std::string& uuid);
  std::map<std::string, std::string> get_link_by_uuid(std::string& uuid);
  std::map<std::string, std::string> get_snapshot_by_uuid(std::string& uuid);
  std::map<std::string, std::string> get_comment_by_uuid(std::string& uuid);

  std::vector<std::map<std::string, std::string>> get_room_users_by_uuid(std::string& uuid);
  std::vector<std::map<std::string, std::string>> get_room_links_by_uuid(std::string& uuid);
  std::vector<std::map<std::string, std::string>> get_link_snapshots_by_uuid(std::string& uuid);
  std::vector<std::map<std::string, std::string>> get_link_comments_by_uuid(std::string& uuid);

  void add_user(std::string& login, std::string& password);
  void add_room(std::string& login, bool private_, std::string& uuid);
  void add_link_to_room(std::string& url, std::string& name, std::string& description, std::string& link_uuid, std::string& room_uuid);
  void add_users_to_room(std::vector<std::string>& users, std::string& room_uuid);
  void add_comment_to_link(std::string& comment_uuid, std::string& content, std::string& link_uuid);
  void add_snapshot_to_link(std::string& snapshot_uuid, std::string& dir_name, std::string& link_uuid);

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
  std::map<std::string, std::string> get_row_by_query(std::string& query);
  std::vector<std::map<std::string, std::string>> get_rows_by_query(std::string& query);
  void exec_query_command(std::string& query);

  PGBackend backend;
};