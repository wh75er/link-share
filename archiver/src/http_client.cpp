#include "http_client.hpp"

http_request::http_request(const std::string &url) {
    std::string::size_type pos = url.find("//");
    /*error*/
    host = url.substr(pos + 2, url.find("/", pos + 2) - pos - 2);
    /*error*/
    query = "GET " + url + " HTTP/1.1\n\r";
    query += "Host: " + host + "\r\n";
    query += "\r\n";
}

http_client::http_client(const std::string &url) {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    /* надо обработать ошибку */
    request = http_request(url);
    memset(&addr, 0, sizeof(addr));
    addr = resolve(url);
}

struct sockaddr_in http_client::resolve(const std::string &url) {
    struct hostent *hp = gethostbyname(url.c_str());
    /*обработать ошибку*/
    char **pAddr = hp->h_addr_list;
    while (*pAddr) {
        unsigned char *ipf = reinterpret_cast<unsigned char *>(*pAddr);
        uint32_t cur_interface_ip = 0;
        uint8_t *rimap_local_ip_ptr =
            reinterpret_cast<uint8_t *>(&cur_interface_ip);
        rimap_local_ip_ptr[0] = ipf[0];
        rimap_local_ip_ptr[1] = ipf[1];
        rimap_local_ip_ptr[2] = ipf[2];
        rimap_local_ip_ptr[3] = ipf[3];
        ++pAddr;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(443);
    memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);

    return addr;
}

http_client::~http_client() {
    int a = 0;
    a++;
}

std::string http_client::create_request(const std::string &url) {
    std::string request = "some string";
    return request;
}

enum client_exit_status http_client::connect() {
    int connected =
        ::connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (connected == -1) {
        return CONNECTION_FAILURE;
    }

    return CONNECTION_SUCCESS;
}

enum client_exit_status http_client::recieve(std::string *path_to_response) {
    return SUCCESS;
}

enum client_exit_status http_client::send(const std::string &request) {
    return CONNECTION_FAILURE;
}
