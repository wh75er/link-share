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

  std::map<std::string, std::string> get_row_by_query(std::string& query);
  std::vector<std::map<std::string, std::string>> get_rows_by_query(std::string& query);
  void exec_query_command(std::string& query);

private:
  PGBackend backend;
};

