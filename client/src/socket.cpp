#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h> 
#include <stdexcept>
#include <string.h>
#include <unistd.h>

#include "socket.hpp"

struct sockaddr_in resolve(const char* host, int port) {
    struct hostent* hp = gethostbyname(host);
    if (hp == NULL)
    throw std::runtime_error("resolve error: " + std::string(strerror(errno)));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);
    
    return addr;
}

void set_non_blocked_impl(int sd, bool opt) {
    int flags = fcntl(sd, F_GETFL, 0);
    int new_flags = (opt) ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    if (fcntl(sd, F_SETFL, new_flags) == -1)
    throw std::runtime_error("make nonblocked: " +
                             std::string(strerror(errno)));
}

void Socket::Connect(const std::string& host, int port) {
    struct sockaddr_in addr = resolve(host.data(), port);

    int _sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_sd <= 0)
        throw std::runtime_error("error to create socket: " +
                             std::string(strerror(errno)));


    int connected = ::connect(_sd, (struct sockaddr*)&addr, sizeof(addr));
    if (connected == -1) {
        ::close(_sd);
        throw std::runtime_error("connect error: " + std::string(strerror(errno)));
    }

    //set_non_blocked_impl(_sd, true);

    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;

    if (setsockopt(_sd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) != 0) {
        throw std::runtime_error("set rcvtimeout: " + std::string(strerror(errno)));
    }

    sd = _sd;
}

void Socket::Send(const std::string& str) {
    size_t left = str.size();
    ssize_t sent = 0;

    int flags = 0;
    while (left > 0) {
        sent = ::send(sd, str.data() + sent, str.size() - sent, flags);
        if (-1 == sent) {
            throw std::runtime_error("write failed: " + std::string(strerror(errno)));
        }
        left -= sent;
  }
}

std::string Socket::Recv() {
    char buf[256];
    std::string ret;

    while (true) {
    int n = ::recv(sd, buf, sizeof(buf), MSG_NOSIGNAL);
    if (-1 == n && errno != EAGAIN) {
        throw std::runtime_error("read failed: " + std::string(strerror(errno)));
    }
    if (0 == n || -1 == n) {
        break;
    }
    ret.append(buf, n);
    while (ret.back() == '\r' || ret.back() == '\n') {
      ret.pop_back();
    }
    }

    return ret;
}

void Socket::Close() {
    ::close(sd);
}