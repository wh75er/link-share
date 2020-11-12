#include "client.hpp"

Client::Client() : sock() {}

Client::~Client() {}

void Client::connect(const std::string& host, int port) {}

std::string Client::readFromServer() { return "str"; }

void Client::writeToServer(std::string& req) {}

void Client::closeCon() {}
