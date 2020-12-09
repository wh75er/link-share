#include "http_client.hpp"

http_request::http_request(const std::string &url) {
    if (url == "\0") {
        throw std::invalid_argument("empty url");
    }

    std::string::size_type host_start_pos = url.find("//");
    if (host_start_pos == std::string::npos) {
        host_start_pos = 0;
    } else {
        host_start_pos += strlen("//");
    }
    std::string::size_type host_end_pos = url.find("/", host_start_pos);
    if (host_end_pos == std::string::npos) {
        host_end_pos = url.size();
    }

    host = url.substr(host_start_pos, host_end_pos - host_start_pos);

    std::string info = url.substr(host_end_pos, url.size() - host_end_pos);
    if (url.size() == host_end_pos) {
        info = "/";
    }
    query = "GET " + info + " HTTP/1.1\r\n";
    query += "Host: " + host + "\r\n";
    query += "\r\n";
}

http_response::http_response(const std::string &response) {
    std::string::size_type code_pos = response.find(" ");
    if (code_pos == std::string::npos) {
        throw std::invalid_argument("broken response");
    } else {
        code = std::stoi(response.substr(code_pos + 1, 3));
    }

    std::string::size_type pos = response.find("\r\n\r\n");

    if (pos == std::string::npos) {
        throw std::invalid_argument("broken response");
    } else {
        query = response.substr(0, pos);
        html_body = response.substr(pos, response.size() - pos);
    }
}

void http_client::socket_setings(const std::string &url) {
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
        throw std::runtime_error("connect error: " +
                                 std::string(strerror(errno)));
    }

    SSL_library_init();
    SSLeay_add_ssl_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD *meth = TLS_client_method();
    if (meth == NULL) {
        int ssl_err = SSL_get_error(ssl, ERR_get_error());
        throw std::runtime_error("cration of a SSL_METHOD object failed: " +
                                 std::string(strerror(ssl_err)));
    }

    SSL_CTX *ctx = SSL_CTX_new(meth);
    if (ctx == NULL) {
        int ssl_err = SSL_get_error(ssl, ERR_get_error());
        throw std::runtime_error("creation of a new SSL_CTX object failed: " +
                                 std::string(strerror(ssl_err)));
    }

    ssl = SSL_new(ctx);
    if (!ssl) {
        int ssl_err = SSL_get_error(ssl, ERR_get_error());
        throw std::runtime_error("creation of a new SSL structure failed: " +
                                 std::string(strerror(ssl_err)));
    }

    int sock_set = SSL_set_fd(ssl, socket_fd);
    if (sock_set == -1) {
        int ssl_err = SSL_get_error(ssl, sock_set);
        throw std::runtime_error("connecting SSL object with a fd failed: " +
                                 std::string(strerror(ssl_err)));
    }

    int err = SSL_connect(ssl);
    if (err != 1) {
        int ssl_err = SSL_get_error(ssl, err);
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

http_client::http_client(const std::string &url) { socket_setings(url); }

http_client::~http_client() {
    ::close(socket_fd);
    SSL_shutdown(ssl);
}

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
    std::string ret = "\0";
    int len = -1;
    char buf[1024];
    bzero(buf, 1024);
    /*
    do {
        len = SSL_read(ssl, buf, 1023);
        if (len < 0) {
            int ssl_err = SSL_get_error(ssl, len);
            throw std::runtime_error("the read operation was not successful: " +
                                     std::string(strerror(ssl_err)));
            return FAILURE;
        }
        // std::cout << buf;
        ret.append(buf, strlen(buf));
        bzero(buf, 1024);
        std::cout << "\n\n|||" << len << "\n\n";
    } while (len >= 0);
    */
    std::cout << request.query << '\n';
    puts("..............\n");
    while (SSL_read(ssl, buf, 1023) >= 0) {
        ret.append(buf, strlen(buf));
        // std::cout << buf;
        bzero(buf, 1024);
    }
    // std::cout << ret;

    response = http_response(ret);
    std::cout << response.query;

    switch (response.code) {
    case 200:
        return SUCCESS;
    case 301:
        return REDIRECT;
    case 302:
        return REDIRECT;
    case 303:
        return REDIRECT;
    case 307:
        return REDIRECT;
    default:
        return FAILURE;
    }
}

const std::string &http_client::get_response() { return response.html_body; };

void http_client::redirect() {
    // std::cout << request.query;
    std::string::size_type pos = response.query.find("Location: ");
    if (pos == std::string::npos) {
        pos = response.query.find("location: ");
        if (pos == std::string::npos) {
            throw std::invalid_argument("redirection location not found");
        }
    }

    std::string buf = response.query.substr(pos + strlen("Location: "),
                                            response.query.size() - pos);

    std::string::size_type end_pos = buf.find("\r\n");
    if (pos == std::string::npos) {
        throw std::invalid_argument("redirection location not found");
    }

    buf = buf.substr(0, end_pos);
    if (buf[0] == '/') {
        request.query = "GET " + buf + " HTTP/1.1\r\n";
        request.query += "Host: " + request.host + "\r\n";
        request.query += "\r\n";
        return;
    }

    ::close(socket_fd);
    socket_setings(buf);
}

void http_client::new_request(const std::string &url) {
    if (url.find("http") != std::string::npos) {
        ::close(socket_fd);
        socket_setings(url);
        return;
    }

    if (url.find("//") != std::string::npos) {
        ::close(socket_fd);
        socket_setings("https:" + url);
        return;
    }

    request.query = "GET /" + url + " HTTP/1.1\r\n";
    request.query += "Host: " + request.host + "\r\n";
    request.query += "\r\n";
    return;
}

enum client_exit_status http_client::send() {
    int len =
        SSL_write(ssl, request.query.c_str(), strlen(request.query.c_str()));
    if (len != strlen(request.query.c_str())) {
        int ssl_err = SSL_get_error(ssl, len);
        throw std::runtime_error("the write operation was not successful: " +
                                 std::string(strerror(ssl_err)));
        return FAILURE;
    }

    return SUCCESS;
}
