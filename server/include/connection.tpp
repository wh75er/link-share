#pragma once

#define RECIVE_BYTE_SIZE 1024

#define PACKAGE_SIZE 400

template<class DbOps, class Uuid, class JsonParser>
Connection<DbOps, Uuid, JsonParser>::Connection(std::shared_ptr<BaseTcpSocket> socket):
        socket_(std::move(socket))
{
#ifdef DEBUG
  std::cout << "Connection constructor" << std::endl;
#endif
}

template<class DbOps, class Uuid, class JsonParser>
std::string Connection<DbOps, Uuid, JsonParser>::read() {
  char buf[RECIVE_BYTE_SIZE];

  std::string ret;
  std::string pkg;

  while (true) {
    int n = socket_->recv_(buf, sizeof(buf));

    if (n == 0) {
      break;
    }

    pkg.append(buf, n);

#ifdef DEBUG
    std::cout << "pkg : " << pkg << std::endl;
#endif

    if (pkg.size() == PACKAGE_SIZE) {
      char status = pkg[0];
      pkg.erase(0, 1);

      ret.append(pkg);

      while (ret.back() == '\r' || ret.back() == '\n' || ret.back() == '\x1A')
        ret.pop_back();

      if (status == 'e' || status == 'f') {
        break;
      }

      pkg.clear();
    }
  }
  return ret;
}

template<class DbOps, class Uuid, class JsonParser>
void Connection<DbOps, Uuid, JsonParser>::write(const std::string& str) {
  size_t left = str.size();

  ssize_t sent = 0;

  while (left > 0) {
    sent = socket_->send_(str.data() + sent, str.size() - sent);
    if (-1 == sent)
      throw std::runtime_error("write failed: " + std::string(strerror(errno)));

    left -= sent;
  }
}

template<class DbOps, class Uuid, class JsonParser>
void Connection<DbOps, Uuid, JsonParser>::start(std::shared_ptr<DbOps> dbops) {
  std::string data = "";
  try {
    data = read();
  }
  catch(const BaseException& except) {
#ifdef DEBUG
    std::cout << "Error occured in connection read! : " << except.what() << std::endl;
#endif
    throw;
  }

#ifdef DEBUG
  std::cout << "Got data from connection" << std::endl;
#endif

  rh = std::make_unique<RequestHandler<DbOps, Connection<DbOps, Uuid, JsonParser>, Uuid, JsonParser>>(this->shared_from_this(), dbops);

  rh->handle(data);
}

template<class DbOps, class Uuid, class JsonParser>
void Connection<DbOps, Uuid, JsonParser>::finish() {
  socket_->close_();
}
