
#include "socket.hpp"

#include <netinet/in.h>
#include <string>
#include <vector>


class Client {
public:
    Client();
    ~Client();
    void connect(const std::string& host, int port);
    void writeToServer(std::string req);
    std::string readFromServer();
    void closeCon();

private:
    Socket sock;
};

