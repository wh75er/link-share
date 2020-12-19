#include "pgconnection.hpp"

PGConnection::PGConnection()
{
  m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), std::to_string(m_dbport).c_str(), nullptr,
                                   nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str())
                      , &PQfinish );

  if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
  {
    throw std::runtime_error( PQerrorMessage( m_connection.get() ) );
  }

}

std::shared_ptr<PGconn> PGConnection::connection() const
{
  return m_connection;
}

PGBackend::PGBackend()
{
  createPool();
}


void PGBackend::createPool()
{
  std::lock_guard<std::mutex> locker_( m_mutex );

  for ( auto i = 0; i< POOL; ++i ){
    m_pool.emplace ( std::make_shared<PGConnection>() );
  }
}

std::shared_ptr<PGConnection> PGBackend::connection()
{
  std::unique_lock<std::mutex> lock_( m_mutex );

  while ( m_pool.empty() ){
    m_condition.wait( lock_ );
  }

  auto conn_ = m_pool.front();
  m_pool.pop();

  return  conn_;
}

void PGBackend::freeConnection(std::shared_ptr<PGConnection> conn_)
{
  std::unique_lock<std::mutex> lock_( m_mutex );
  m_pool.push( conn_ );
  lock_.unlock();
  m_condition.notify_one();
}


std::map<std::string, std::string> DbOps::get_row_by_query(std::string& query) {
  auto conn = backend.connection();

  PQsendQuery(conn->connection().get(), query.c_str());

  std::string error = "";

  std::map<std::string, std::string> row;
  while (auto res = PQgetResult(conn->connection().get())) {
    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
      int n_tuples = PQntuples(res);

      if (!n_tuples) {
        throw std::runtime_error("empty");
      }

      int n = PQnfields(res);
      for (auto i = 0; i < n; i++) {
        std::string key = PQfname(res, i);
        std::string value = PQgetvalue(res, 0, i);
        row[key] = value;
      }
    } else {
      error = PQresultErrorMessage(res);
    }

    PQclear(res);
  }

  backend.freeConnection(conn);

  if (!error.empty()) {
    throw std::runtime_error("Error occurred : " + error + "!");
  }

  return row;
}

std::map<std::string, std::string> DbOps::get_user_by_login(std::string &login) {
  std::string query = "SELECT * FROM users where login='" + login + "';";

  std::map<std::string, std::string> row;

  try {
    row = get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

std::map<std::string, std::string> DbOps::get_room_by_uuid(std::string &uuid) {
  std::string query = "SELECT * FROM rooms where room_uuid='" + uuid + "';";

  std::map<std::string, std::string> row;

  try {
    row = get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

std::map<std::string, std::string> DbOps::get_link_by_uuid(std::string &uuid) {
  std::string query = "SELECT * FROM link where link_uuid='" + uuid + "';";

  std::map<std::string, std::string> row;

  try {
    row = get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

std::map<std::string, std::string> DbOps::get_snapshot_by_uuid(std::string &uuid) {
  std::string query = "SELECT * FROM snapshots where snapshot_uuid='" + uuid + "';";

  std::map<std::string, std::string> row;

  try {
    row = get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

std::map<std::string, std::string> DbOps::get_comment_by_uuid(std::string &uuid) {
  std::string query = "SELECT * FROM comments where comment_uuid='" + uuid + "';";

  std::map<std::string, std::string> row;

  try {
    row = get_row_by_query(query);
  }
  catch (...) {
    throw;
  }

  return row;
}

std::vector<std::map<std::string, std::string>> DbOps::get_rows_by_query(std::string &query) {
  auto conn = backend.connection();

  PQsendQuery(conn->connection().get(), query.c_str());

  std::string error = "";

  std::vector<std::map<std::string, std::string>> rows;
  while (auto res = PQgetResult(conn->connection().get())) {
    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
      int n_tuples = PQntuples(res);

      if (!n_tuples) {
        throw std::runtime_error("empty");
      }

      int n_fields = PQnfields(res);
      for(int i = 0; i < n_tuples; i++) {
        std::map<std::string, std::string> row;
        for (auto j = 0; j < n_fields; j++) {
          std::string key = PQfname(res, j);
          std::string value = PQgetvalue(res, i, j);
          row[key] = value;
        }
        rows.push_back(row);
      }
    } else {
      error = PQresultErrorMessage(res);
    }

    PQclear(res);
  }

  backend.freeConnection(conn);

  if (!error.empty()) {
    throw std::runtime_error("Error occurred : " + error + "!");
  }

  return rows;
}

std::vector<std::map<std::string, std::string>> DbOps::get_room_users_by_uuid(std::string &uuid) {
  std::string query = "select * from users where id in "
                      "(select user_id from room_users where room_id="
                      "(select id from rooms where room_uuid='" + uuid + "'));";

  std::vector<std::map<std::string, std::string>> rows;

  try {
    rows = get_rows_by_query(query);
  }
  catch (...) {
    throw;
  }

  return rows;
}

std::vector<std::map<std::string, std::string>> DbOps::get_room_links_by_uuid(std::string &uuid) {
  std::string query = "select * from web_links where id in "
                      "(select link_id from room_links where room_id="
                      "(select id from rooms where room_uuid='" + uuid + "'))";

  std::vector<std::map<std::string, std::string>> rows;

  try {
    rows = get_rows_by_query(query);
  }
  catch (...) {
    throw;
  }

  return rows;
}

std::vector<std::map<std::string, std::string>> DbOps::get_link_snapshots_by_uuid(std::string &uuid) {
  std::string query = "select * from snapshots where link_id in "
                      "(select id from web_links where link_uuid='" + uuid + "');";

  std::vector<std::map<std::string, std::string>> rows;

  try {
    rows = get_rows_by_query(query);
  }
  catch (...) {
    throw;
  }

  return rows;
}

std::vector<std::map<std::string, std::string>> DbOps::get_link_comments_by_uuid(std::string &uuid) {
  std::string query = "select * from comments where link_id in "
                      "(select id from web_links where link_uuid='" + uuid + "');";

  std::vector<std::map<std::string, std::string>> rows;

  try {
    rows = get_rows_by_query(query);
  }
  catch (...) {
    throw;
  }

  return rows;
}

void DbOps::exec_query_command(std::string &query) {
  auto conn = backend.connection();

  PQsendQuery(conn->connection().get(), query.c_str());

  std::string error = "";

  while (auto res = PQgetResult(conn->connection().get())) {
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      error = PQresultErrorMessage(res);
    }

    PQclear(res);
  }

  backend.freeConnection(conn);

  if (!error.empty()) {
    throw std::runtime_error("Error occurred : " + error + "!");
  }
}

void DbOps::add_user(std::string &login, std::string &password) {
  std::string query = "insert into users (login, password) values ('" + login + "', '" + password + "');";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::add_room(std::string& login, bool private_, std::string &uuid) {
  std::string boolean = private_ ? "true" : "false";
  std::string query = "insert into rooms (room_uuid, private, room_date, user_id) values "
                      "('" + uuid + "', " + boolean + ", NOW(), (select id from users where login='" + login + "'));";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::add_link_to_room(std::string& url, std::string& name, std::string& description, std::string& link_uuid, std::string& room_uuid) {
  std::string query1 = "insert into web_links (url, name, description, link_date, link_uuid) values "
                      "('" + url + "', '" + name + "', '" + description + "', NOW(), '" + link_uuid + "');";

  std::string query2 = "insert into room_links (room_id, link_id) values "
                       "((select id from rooms where room_uuid='" + room_uuid + "'), "
                       "(select id from links where link_uuid='" + link_uuid + "'));";

  try {
    exec_query_command(query1);
    exec_query_command(query2);
  }
  catch (...) {
    throw;
  }
}

void DbOps::add_users_to_room(std::vector<std::string> &users, std::string &room_uuid) {
  for (auto i = 0; i < users.size(); i++) {
    std::string query = "insert into room_users (room_id, user_id) values "
                        "((select id from rooms where room_uuid='" + room_uuid + "'), "
                        "(select id from users where login='" + users[i] + "'));";

    try {
      exec_query_command(query);
    }
    catch (...) {
      throw;
    }
  }
}

void DbOps::add_comment_to_link(std::string& comment_uuid, std::string& content, std::string &link_uuid) {
  std::string query = "insert into comments (comment_uuid, content, link_id) values "
                      "('" + comment_uuid + "', '" + content + "', "
                      "(select id from web_links where link_uuid='" + link_uuid + "'));";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::add_snapshot_to_link(std::string& snapshot_uuid, std::string& dir_name, std::string& link_uuid) {
  std::string query = "insert into snapshots (snapshot_uuid, dir_name, link_id, snapshot_date) values "
                      "('" + snapshot_uuid + "', '" + dir_name + "', "
                      "(select id from web_links where link_uuid='" + link_uuid + "'), "
                      "NOW());";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::delete_room(std::string &room_uuid) {
  std::string query = "delete from rooms where room_uuid='" + room_uuid + "';";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::delete_link(std::string &link_uuid) {
  std::string query = "delete from web_links where link_uuid='" + link_uuid + "';";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::delete_link_from_room(std::string &link_uuid, std::string &room_uuid) {
  std::string query = "delete from room_links where link_id=(select id from web_links where link_uuid='" + link_uuid + "') and "
                                                    "room_id=(select id from rooms where room_uuid='" + room_uuid + "');";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::delete_links_from_room(std::string &room_uuid) {
  std::string query = "delete from room_links where room_id=(select id from rooms where room_uuid='" + room_uuid + "');";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::delete_users_from_room(std::vector<std::string>& users, std::string& room_uuid) {
  for (auto i = 0; i < users.size(); i++) {
    std::string query = "delete from room_users where user_id=(select id from users where login='" + users[i] +"') and "
                                                     "room_id=(select id from rooms where room_uuid='" + room_uuid + "');";
    try {
      exec_query_command(query);
    }
    catch (...) {
      throw;
    }
  }
}

void DbOps::delete_users_from_room(std::string &room_uuid) {
  std::string query = "delete from room_users where room_id=(select id from rooms where room_uuid='" + room_uuid + "');";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::delete_comment(std::string &comment_uuid) {
  std::string query = "delete from comments where comment_uuid='" + comment_uuid + "';";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::delete_snapshot(std::string &snapshot_uuid) {
  std::string query = "delete from snapshots where snapshot_uuid='" + snapshot_uuid + "';";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::delete_link_snapshots(std::string &link_uuid) {
  std::string query = "delete from snapshots where link_id=(select id from web_links where link_uuid='" + link_uuid + "');";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}

void DbOps::delete_link_comments(std::string &link_uuid) {
  std::string query = "delete from comments where link_id=(select id from web_links where link_uuid='" + link_uuid + "');";

  try {
    exec_query_command(query);
  }
  catch (...) {
    throw;
  }
}