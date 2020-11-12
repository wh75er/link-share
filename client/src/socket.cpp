
#include "socket.hpp"


Socket::Socket() : sd(0) {}

Socket::Socket(int _sd) : sd(_sd) {}

Socket::~Socket() {}

void Socket::connect(const std::string& host, int port) {}
void Socket::send(const std::string& str) {}
std::string Socket::recv() {return "str";}
void Socket::close() {}