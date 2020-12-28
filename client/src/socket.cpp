#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h> 
#include <stdexcept>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <unistd.h>
#include <iostream>

#include "socket.hpp"

#define BUFSIZE 400

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


std::vector<std::string> form_packages(std::string data, char status) {
    std::vector<std::string> pkgs;

  std::string pkg;
  if (data.size() <= BUFSIZE-1) {
    pkg += status;
    pkg += data;
    
    for (size_t i = 0; i < BUFSIZE - 1 - data.size(); i++) {
      pkg += '\x1A';
    }
    pkgs.push_back(pkg);
    pkg.clear();
  } else {
    while(!data.empty()) {
      if (data.size() <= BUFSIZE-1) {
        pkg += status;
      } else {
        pkg += 'c';
      }

      pkg += data.substr(0, BUFSIZE-1);
      data.erase(0, BUFSIZE-1);

      while (pkg.size() < BUFSIZE) {
        pkg += '\x1A';
      }

      pkgs.push_back(pkg);
      pkg.clear();
    }
  }

  return pkgs;
}

void Socket::Send(const std::string& data) {
    std::vector<std::string> pkgs = form_packages(data, 'f');
    for(auto& str : pkgs) {
        size_t left = str.size();

        ssize_t sent = 0;

        while (left > 0) {
            sent = ::send(sd, str.data() + sent, str.size() - sent, 0);
            if (-1 == sent)
            throw std::runtime_error("write failed: " + std::string(strerror(errno)));

            left -= sent;
        }
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

std::string Socket::RecvFile(bool* endFlag) {
    char buf[BUFSIZE];
    std::string ret;

    while (true) {
        int n = ::recv(sd, buf, BUFSIZE, MSG_NOSIGNAL);
        std::string str(buf);
        if (n > 0)
        if (n != BUFSIZE && n != -1) {
            char* bufPtr = buf + n;
            n = ::recv(sd, bufPtr, BUFSIZE - n, MSG_NOSIGNAL);
        }

        if (-1 == n && errno != EAGAIN) {
            throw std::runtime_error("read failed: " + std::string(strerror(errno)));
        }
        if (-1 == n && ret.empty()) {
            continue;
        }
        if (0 == n || -1 == n) {
            break;
        }
        ret.append(buf, 1, BUFSIZE - 1);
        while (ret.back() == '\x1A') {
            ret.pop_back();
        }

    
        if (buf[0] == 'e') {
            
            break;
        } else if (buf[0] == 'f') {
            *endFlag = true;
            break;
        }
    }
    return ret;
}


std::vector<char> Socket::RecvFileVec(bool* endFlag) {
    char buf[BUFSIZE];
    std::vector<char> ret;
    size_t i = 0;
    while (true) {
        int n = ::recv(sd, buf, sizeof(buf), MSG_NOSIGNAL);
        std::string str(buf);
        if (n > 0) {
        }

        if (n != BUFSIZE && n != -1) {
            char* bufPtr = buf + n;
            n = ::recv(sd, bufPtr, BUFSIZE - n, MSG_NOSIGNAL);
        }
        if (-1 == n && errno != EAGAIN) {
            throw std::runtime_error("read failed: " + std::string(strerror(errno)));
        }
        if (-1 == n && ret.empty() && i < 3) {
            sleep(2);
            i++;
            continue;
        }
        if (0 == n || -1 == n) {
            break;
        }

        std::copy(&buf[1], &buf[BUFSIZE], std::back_inserter(ret));
        while (ret.back() == '\x1A') {
            ret.pop_back();
        }

        if (buf[0] == 'e') {
            break;
        } else if (buf[0] == 'f') {
            *endFlag = true;
            break;
        }
    }
    return ret;
}

void Socket::Close() {
    ::close(sd);
}