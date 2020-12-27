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
        //throw std::runtime_error("empty");
        return row;
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

std::vector<std::map<std::string, std::string>> DbOps::get_rows_by_query(std::string &query) {
  auto conn = backend.connection();

  PQsendQuery(conn->connection().get(), query.c_str());

  std::string error = "";

  std::vector<std::map<std::string, std::string>> rows;
  while (auto res = PQgetResult(conn->connection().get())) {
    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
      int n_tuples = PQntuples(res);

      if (!n_tuples) {
        //throw std::runtime_error("empty");
        return rows;
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
