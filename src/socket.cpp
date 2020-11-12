
#include "socket.hpp"


Socket::Socket() {}

Socket::Socket(int sd) {}

Socket::~Socket() {}

void Socket::connect(const std::string& host, int port) {}
void Socket::send(const std::string& str) {}
std::string Socket::recv() {}
void Socket::close() {}