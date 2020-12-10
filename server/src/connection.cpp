#include "connection.hpp"

#define RECIVE_BYTE_SIZE 1024

Connection::Connection(std::shared_ptr<BaseTcpSocket> socket): 
  socket_(socket)
{
#ifdef DEBUG
  std::cout << "Connection constructor" << std::endl;
#endif
}

std::string Connection::read() {
  char buf[256];
  std::string ret;
  while (true) {
    int n = socket_->recv_(buf, sizeof(buf));

    if (-1 == n && errno != EAGAIN) {
      throw std::runtime_error("read failed: " + std::string(strerror(errno)));
    }

    if (0 == n || -1 == n)  // -1 - timeout
      break;

    ret.append(buf, n);

    while (ret.back() == '\r' || ret.back() == '\n')
      ret.pop_back();
  }
  return ret;
}

void Connection::write(const std::string& str) {
  size_t left = str.size();

  ssize_t sent = 0;

  while (left > 0) {
    sent = socket_->send_(str.data() + sent, str.size() - sent);
    if (-1 == sent)
      throw std::runtime_error("write failed: " + std::string(strerror(errno)));

    left -= sent;
  }
}

void Connection::start() {
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

  rh = std::make_unique<RequestHandler>(shared_from_this());

  rh->handle(data);
}

void Connection::finish() {
  socket_->close_();
}
