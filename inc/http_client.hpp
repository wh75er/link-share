#include <iostream>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

enum client_exit_status {
    SUCCESS,
    CONNECTION_ERROR,
    BAD_REQUEST_ERROR,
    SOCKET_CREATION_ERROR
    /* some other errors */
};

class http_client {
public:
    http_client();
    enum client_exit_status recieve(std::string &path_to_response){};
    enum client_exit_status send(const std::string &request){};
    const std::string &create_request(const std::string &url){};

private:
    int socket_fd;
    int ssl_socket_fd;
    SSL *ssl;
    sockaddr_in socket_adress;
};