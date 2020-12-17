#include "https_socket.hpp"
#include <fstream>
#include <sstream>

#define BUFFSIZE 1024
#define TIMEOUT 3

HttpsSocket::HttpsSocket(const std::string &url) : Socket(url) {
    SSLSettings();
}

HttpsSocket::~HttpsSocket() {
    SSL_shutdown(ssl);
    SSL_free(ssl);
    ::close(socketFd);
}

void HttpsSocket::SSLSettings() {
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

    int sock_set = SSL_set_fd(ssl, socketFd);
    if (sock_set == -1) {
        int ssl_err = SSL_get_error(ssl, sock_set);
        throw std::runtime_error("connecting SSL object with a fd failed: " +
                                 std::string(strerror(ssl_err)));
    }

    size_t i = 0;
    int err = SSL_connect(ssl);
    while (i < 3 && err != 1) {
        err = SSL_connect(ssl);
        ++i;
        sleep(TIMEOUT);
    } //периодически падает по непонятным причинам

    if (err != 1) {
        int ssl_err = SSL_get_error(ssl, err);
        throw std::runtime_error("TLS/SSL handshake was not saccessful: " +
                                 std::string(strerror(ssl_err)));
    }

    SSL_CTX_free(ctx);
}

void HttpsSocket::__send() {
    int len =
        SSL_write(ssl, request.query.c_str(), strlen(request.query.c_str()));
    if (len != strlen(request.query.c_str())) {
        int ssl_err = SSL_get_error(ssl, len);
        throw std::runtime_error("the write operation was not successful: " +
                                 std::string(strerror(ssl_err)));
    }
}

char *HttpsSocket::__recv(int *size) {
    int len = 1;
    char *buf = (char *)malloc(BUFFSIZE * sizeof(char));
    bzero(buf, BUFFSIZE);
    char *buf_ptr = buf;
    while (len > 0) {
        len = SSL_read(ssl, buf_ptr, BUFFSIZE);
        *size += len;
        buf = (char *)realloc(buf, *size + BUFFSIZE);
        if (buf == nullptr) {
            throw std::bad_alloc();
        }
        buf_ptr = buf + *size;
    }
    
    buf_ptr = nullptr;

    return buf;
}

void HttpsSocket::redirect() {
    response.findRedirectLocation();

    request = HttpRequest(response.redirectLocation);

    resolve(request.host);
    socketSettings();
    SSLSettings();
}

void HttpsSocket::createNewRequest(const std::string &url) {
    if (url.find("http") != std::string::npos) {
        request = HttpRequest(response.redirectLocation);

        resolve(request.host);
        socketSettings();
        SSLSettings();
        return;
    }

    if (url.find("//") != std::string::npos) {
        request = HttpRequest("https:" + response.redirectLocation);

        resolve(request.host);
        socketSettings();
        SSLSettings();
        return;
    }

    if (url[0] == '/') {
        request.query = "GET " + url + " HTTP/1.1\r\n";
        request.query += "Host: " + request.host + "\r\n";
        request.query += "\r\n";
        return;
    }

    request.query = "GET /" + url + " HTTP/1.1\r\n";
    request.query += "Host: " + request.host + "\r\n";
    request.query += "\r\n";
    return;
}
