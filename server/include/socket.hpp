#pragma once

#include <fcntl.h>
#include <netdb.h>
#include <stdexcept>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "errors.hpp"

#define NON_INITIALIZED_FD -1
#define DEFAULT_MAXIMUM_CONNECTIONS 10

class BaseTcpSocket {
  public:
    BaseTcpSocket();
    virtual ~BaseTcpSocket();

    virtual int create();
    virtual int bind_();
    virtual int listen_();
    virtual int accept_();
    virtual ssize_t send_(const void *msg);
    virtual ssize_t recv_(void *buf, size_t len);
    virtual void close_();
};

class TcpSocket : public BaseTcpSocket {
  public:
    class Builder;

    TcpSocket(
        int _domain,
        char* _address,
        char* _port,
        bool _non_blocking,
        size_t _max_listen_connections
      );
    TcpSocket(
        int _sd,
        int _domain,
        char* _address,
        char* _port,
        bool _non_blocking,
        size_t _max_listen_connections
      );
    ~TcpSocket();

    int create() override;
    int bind_() override;
    int listen_() override;
    int accept_() override;
    ssize_t send_(const void *msg) override;
    ssize_t recv_(void *buf, size_t len) override;
    void close_() override;

  private:
    int sd;
    int domain;
    char *address = nullptr;
    char *port = nullptr;
    struct addrinfo *servinfo = nullptr;
    bool non_blocking = false;
    size_t max_listen_connections;
};

class TcpSocket::Builder {
  public:
    Builder();
    ~Builder();

    Builder& socket(int __sd);
    Builder& domain(int __domain);
    Builder& address(char *__address);
    Builder& address(std::string &__address);
    Builder& port(char *__port);
    Builder& port(std::string &__port);
    Builder& non_blocking();
    Builder& max_listen_connections(size_t __max_listen_connections);
    TcpSocket build() const;

  private:
    int _sd = NON_INITIALIZED_FD;
    int _domain = AF_INET;
    char *_address = nullptr;
    char *_port = nullptr;
    struct _addrinfo *servinfo = nullptr;
    bool _non_blocking = false;
    size_t _max_listen_connections = DEFAULT_MAXIMUM_CONNECTIONS;
};
