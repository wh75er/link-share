#include <iostream>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

enum client_exit_status {
    SUCCESS,
    CONNECTION_FAILURE,
    CONNECTION_SUCCESS,
    BAD_REQUEST_ERROR,
    SOCKET_CREATION_ERROR,
    RESOLV_ERROR
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
};

class http_client {
public:
    http_client(const std::string &url);
    http_client(const http_client &other) = delete;
    http_client &operator=(const http_client &other) = delete;
    ~http_client();

    enum client_exit_status connect();
    enum client_exit_status recieve(std::string *path_to_response);
    enum client_exit_status send(const std::string &request);
    std::string create_request(const std::string &url);

private:
    int socket_fd;
    http_request request;
    http_response response;
    struct sockaddr_in addr;
    struct sockaddr_in resolve(const std::string &url);
};
