#include "client.hpp"

Client::Client(const std::string& _host, int _port) : host(_host), port(_port), sock(-1) {}

void Client::Connect() {
    sock.Connect(host, port);
}

std::string Client::readFromServer() { 
    return sock.Recv();
}

void Client::writeToServer(std::string& req) {
    sock.Send(req);
}


