#pragma once
#include <netinet/in.h>
#include <string>

#include "socket.hpp"
#include "socket.hpp"



class Client {
public:
    Client(const std::string& _host, int _port);
    ~Client() {}
    void Connect();
    void writeToServer(std::string& req);
    std::string readFromServer();
private:
    const std::string& host;
    int port;
    Socket sock;
};

