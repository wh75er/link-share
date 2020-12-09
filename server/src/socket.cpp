#include "socket.hpp"

#define TRY_AGAIN -1

TcpSocket::TcpSocket(
  int _sd, 
  int _domain,
  char* _address,
  char* _port,
  bool _non_blocking,
  size_t _max_listen_connections
) : sd(_sd),
    domain(_domain),
    address(_address),
    port(_port),
    non_blocking(_non_blocking),
    max_listen_connections(_max_listen_connections)
{}

TcpSocket::TcpSocket(
  int _domain,
  char* _address,
  char* _port,
  bool _non_blocking,
  size_t _max_listen_connections
) : domain(_domain),
    address(_address),
    port(_port),
    non_blocking(_non_blocking),
    max_listen_connections(_max_listen_connections)
{}

TcpSocket::Builder& TcpSocket::Builder::socket(int __sd) {
  _sd = __sd;
  return *this;
}

TcpSocket::Builder& TcpSocket::Builder::domain(int __domain) {
  _domain = __domain;
  return *this;
}

TcpSocket::Builder& TcpSocket::Builder::address(char *__address) {
  _address = __address;
  return *this;
}

TcpSocket::Builder& TcpSocket::Builder::address(std::string &__address) {
  _address = (char *)__address.c_str();
  return *this;
}

TcpSocket::Builder& TcpSocket::Builder::port(char *__port) {
  _port = __port;
  return *this;
}

TcpSocket::Builder& TcpSocket::Builder::port(std::string &__port) {
  _port = (char *)__port.c_str();
  return *this;
}

TcpSocket::Builder& TcpSocket::Builder::non_blocking() {
  _non_blocking = true;
  return *this;
}

TcpSocket::Builder& TcpSocket::Builder::max_listen_connections(size_t __max_listen_connections) {
  _max_listen_connections = __max_listen_connections;
  return *this;
}

TcpSocket TcpSocket::Builder::build() const {
  return TcpSocket(
      _sd,
      _domain,
      _address,
      _port,
      _non_blocking,
      _max_listen_connections
    );
}

TcpSocket::~TcpSocket() {
  freeaddrinfo(servinfo);
  close(sd);
}

int TcpSocket::create() {

  struct addrinfo hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = domain;
  hints.ai_socktype = SOCK_STREAM;

  if (!address) {
    hints.ai_flags = AI_PASSIVE;
  }

  int status = 0;
  if ((status = getaddrinfo(address, port, &hints, &servinfo))) {
    throw AddrInfoException(
        AddrInfoDefaultError(status)
    );
  }

  if ((status = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) < 0) {
    throw SocketException(
        SocketDefaultError(errno)
    );
  }

  sd = status;

  return sd;
}

int TcpSocket::bind_() {
  int status = 0;
  if ((status = bind(sd, servinfo->ai_addr, servinfo->ai_addrlen)) < 0) {
    throw SocketException(
        SocketDefaultError(errno)
    );
  }

  return status;
}

int TcpSocket::listen_() {
  int status = 0;
  if ((status = listen(sd, max_listen_connections)) < 0) {
    throw SocketException(
        SocketDefaultError(errno)
    );
  }

  return status;
}

int TcpSocket::accept_() {

  struct sockaddr_storage client_addr;
  socklen_t addr_size = sizeof(client_addr);

  int socket_descriptor = 0;
  if ((socket_descriptor = accept(sd, (struct sockaddr *)&client_addr, &addr_size)) < 0) {
    if (errno != EAGAIN && errno != EWOULDBLOCK) {
      throw SocketException(
          SocketDefaultError(errno)
      );
    } else {
      return TRY_AGAIN;
    }
  }

  return socket_descriptor;
}

ssize_t TcpSocket::send_(const void *msg) {
  ssize_t bytes_sent = 0;

  if ((bytes_sent = send(sd, msg, sizeof(msg), 0)) == -1) {
    throw SocketException(
        SocketDefaultError(errno)
    );
  }

  return bytes_sent;
}

ssize_t TcpSocket::recv_(void *buf, size_t len) {
  ssize_t bytes_recv = 0;

  if ((bytes_recv = recv(sd, buf, len, 0)) == -1) {
    throw SocketException(
        SocketDefaultError(errno)
    );
  }
  
  return bytes_recv;
}

void TcpSocket::close_() {
  if (close(sd) < 0) {
    throw SocketException(
        SocketDefaultError(errno)
    );
  }

  sd = NON_INITIALIZED_FD;
}
