#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

enum client_exit_status {
    SUCCESS,
    REDIRECT,
    FAILURE
    /* some other errors */
};

struct http_request {
    http_request() : query("\0"), host("\0"){};
    http_request(const std::string &url);
    std::string query;
    std::string host;
};

struct http_response {
    http_response() : query("\0"), html_body("\0"){};
    http_response(const std::string &response);
    std::string query;
    std::string html_body;
    size_t code;
};

class http_client {
public:
    http_client(const std::string &url);
    http_client(const http_client &other) = delete;
    ~http_client();

    enum client_exit_status recieve();
    enum client_exit_status send();

    const std::string &get_response();

    void redirect();
    // void create_new_request();

private:
    int socket_fd;
    SSL *ssl;
    http_request request;
    http_response response;
    struct sockaddr_in addr;
    struct sockaddr_in resolve(const std::string &url);
};
