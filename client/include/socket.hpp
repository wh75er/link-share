#pragma once

#include <unistd.h>  // close()
#include <memory>
#include <string>

class Socket
{
public:
    Socket() : sd (-1) {}
    Socket(int _sd) : sd(_sd) {}
    ~Socket() {
        if (sd > 0) {
            ::close(sd);
        }
    }

    int GetSd() {
        return sd;
    }
    void Connect(const std::string& host, int port);
    void Send(const std::string& str);
    std::string Recv();
    void Close();
private:
    int sd;
};