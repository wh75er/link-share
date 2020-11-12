#include "http_client.hpp"

http_client::http_client() { socket_fd = 0; }

http_client::~http_client() {
    int a = 0;
    a++;
}

std::string http_client::create_request(const std::string &url) {
    std::string request = "some string";
    return request;
}

enum client_exit_status http_client::connect(const std::string &url) {
    return BAD_REQUEST_ERROR;
}

enum client_exit_status http_client::recieve(std::string *path_to_response) {
    return SUCCESS;
}

enum client_exit_status http_client::send(const std::string &request) {
    return CONNECTION_ERROR;
}
