#include "client.hpp"

Client::Client(const std::string& _host, int _port) : host(_host), port(_port), sock(-1) {}

void Client::Connect() {
    sock.Connect(host, port);
}

void Client::Close() {
    sock.Close();
}

std::string Client::readFromServer() {
    bool endFlag = false;
    return sock.RecvFile(endFlag);
}

void Client::writeToServer(std::string& req) {
    
    sock.Send(req);
}