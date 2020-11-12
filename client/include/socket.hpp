#pragma once

#include <unistd.h>  // close()
#include <memory>
#include <string>


class Socket
{
public:
    Socket();
    Socket(int _sd);
    ~Socket();

    void connect(const std::string& host, int port);
    void send(const std::string& str);
    std::string recv();
    void close();
private:
    int sd;
};