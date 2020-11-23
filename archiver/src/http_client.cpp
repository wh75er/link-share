#include "http_client.hpp"

http_request::http_request(const std::string &url) {
    std::string::size_type host_start_pos = url.find("//");
    if (host_start_pos == std::string::npos) {
        host_start_pos = 0;
    } else {
        host_start_pos += 2;
    }
    std::string::size_type host_end_pos = url.find("/", host_start_pos);
    if (host_end_pos == std::string::npos) {
        host_end_pos = url.size();
    }

    host = url.substr(host_start_pos, host_end_pos - host_start_pos);

    std::string info = url.substr(host_end_pos, url.size() - host_end_pos);
    if (url.size() == host_end_pos) {
        info = host;
    }
    query = "GET " + info + " HTTP/1.1\n\r";
    query += "Host: " + host + "\r\n";
    query += "\r\n";
}

http_response::http_response(const std::string &response) {
    std::string::size_type pos = response.find("<!doctype html>");
    query = response.substr(0, pos);
    html_body = response.substr(pos, response.length() - pos);
}

http_client::http_client(const std::string &url) {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    /* надо обработать ошибку */
    if (socket_fd == -1) {
        std::cout << "failconnect1";
    }
    request = http_request(url);
    memset(&addr, 0, sizeof(addr));

    addr = resolve(request.host);

    int connected =
        ::connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (connected == -1) {
        std::cout << "asd";
        std::cout << connected;
        std::cout << errno;
    }

    SSL_library_init();
    SSLeay_add_ssl_algorithms();
    const SSL_METHOD *meth = TLS_client_method();
    SSL_CTX *ctx = SSL_CTX_new(meth);
    ssl = SSL_new(ctx);
    /*error*/
    if (!ssl) {
        std::cout << "failconnect2";
    }

    int sock = SSL_get_fd(ssl);
    /*error*/
    SSL_set_fd(ssl, socket_fd);

    int err = SSL_connect(ssl);
    if (err <= 0) {
        std::cout << "huy" << err << SSL_get_error(ssl, err);
    }
}

http_client::~http_client() { socket_fd = 0; }

enum client_exit_status http_client::connect() {

    /*error*/

    return CONNECTION_SUCCESS;
}

struct sockaddr_in http_client::resolve(const std::string &url) {
    struct hostent *hp = gethostbyname(url.c_str());
    /*обработать ошибку*/

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(443);
    memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);

    return addr;
}

std::string http_client::create_request(const std::string &url) {
    std::string request = "some string";
    return request;
}

enum client_exit_status http_client::recieve(std::string *response) {
    int len = 100;
    char buf[10000];
    do {
        len = SSL_read(ssl, buf, 100);
        buf[len] = 0;
        printf("%s\n", buf);
    } while (len > 0);
    return SUCCESS;
}

enum client_exit_status http_client::send() {
    std::cout << request.query.c_str() << '\n';
    int len =
        SSL_write(ssl, request.query.c_str(), strlen(request.query.c_str()));
    if (len < 0) {
        std::cout << "ne otpravilos";
    }
    return CONNECTION_FAILURE;
}
