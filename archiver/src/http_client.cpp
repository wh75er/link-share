#include "http_client.hpp"

http_request::http_request(const std::string &url) {
    if (url == "\0") {
        throw std::invalid_argument("empty url");
    }

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
    query = "GET " + info + " HTTP/1.1\r\n";
    query += "Host: " + host + "\r\n";
    query += "\r\n";
}

http_response::http_response(const std::string &response) {
    std::string::size_type pos = response.find("<!DOCTYPE html>");
    if (pos == std::string::npos) {
        pos = response.find("<!doctype html>");
    }
    query = response.substr(0, pos);
    html_body = response.substr(pos, response.length() - pos);
}

http_client::http_client(const std::string &url) {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        throw std::runtime_error("connection error: " +
                                 std::string(strerror(errno)));
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
    SSL_load_error_strings();
    const SSL_METHOD *meth = TLS_client_method();
    if (meth == NULL) {
        int ssl_err = SSL_get_error(ssl, ssl_err);
        throw std::runtime_error("cration of a SSL_METHOD object failed: " +
                                 std::string(strerror(ssl_err)));
    }
    SSL_CTX *ctx = SSL_CTX_new(meth);
    if (ctx == NULL) {
        int ssl_err = SSL_get_error(ssl, ssl_err);
        throw std::runtime_error("creation of a new SSL_CTX object failed: " +
                                 std::string(strerror(ssl_err)));
    }
    ssl = SSL_new(ctx);
    if (!ssl) {
        int ssl_err = SSL_get_error(ssl, ssl_err);
        throw std::runtime_error("creation of a new SSL structure failed: " +
                                 std::string(strerror(ssl_err)));
    }

    int sock_set = SSL_set_fd(ssl, socket_fd);
    if (sock_set == -1) {
        int ssl_err = SSL_get_error(ssl, ssl_err);
        throw std::runtime_error("connecting SSL object with a fd failed: " +
                                 std::string(strerror(ssl_err)));
    }

    int err = SSL_connect(ssl);
    if (err != 1) {
        int ssl_err = SSL_get_error(ssl, ssl_err);
        throw std::runtime_error("TLS/SSL handshake was not saccessful: " +
                                 std::string(strerror(ssl_err)));
    }

    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) != 0) {
        throw std::runtime_error("rcvtimeout: " + std::string(strerror(errno)));
    }
}

http_client::~http_client() { ::close(socket_fd); }

struct sockaddr_in http_client::resolve(const std::string &url) {
    struct hostent *hp = gethostbyname(url.c_str());
    if (hp == NULL) {
        throw std::runtime_error("getting of hostent failed: " +
                                 std::string(strerror(h_errno)));
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(443);
    memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);

    return addr;
}

enum client_exit_status http_client::recieve() {
    std::string ret;
    int len = 1;
    char buf[1024];
    bzero(buf, 1024);
    do {
        len = SSL_read(ssl, buf, 1024 - 1);
        ret.append(buf, strlen(buf));
        bzero(buf, 1024);
    } while (len > 0);

    response = http_response(ret);
    std::ofstream my_out("new.html");
    my_out << response.html_body;
    return SUCCESS;
}

std::string http_client::create_request(const std::string &url) {
    std::string request = "some string";
    return request;
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
