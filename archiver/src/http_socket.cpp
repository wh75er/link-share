#include "http_socket.hpp"
#include <algorithm>
#include <iostream>

#define TIMEOUT 3

void HttpRequest::findHost(const std::string &url) {
    if (url.empty()) {
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
}

void HttpRequest::createQuery(const std::string &url) {
    if (url.empty()) {
        throw std::invalid_argument("empty url");
    }

    std::string info;
    if (url.size() == host.size()) {
        info = "/";
    } else {
        std::string::size_type info_start_pos = url.find(host);
        info_start_pos += host.size();
        info = url.substr(info_start_pos, url.size() - info_start_pos);
    }

    query = "GET " + info + " HTTP/1.1\r\n";
    query += "Host: " + host + "\r\n";
    query += "\r\n";
}

HttpRequest::HttpRequest(const std::string &url) {
    findHost(url);
    createQuery(url);
}

void HttpResponse::createQuery(const std::string &response) {
    std::string::size_type pos = response.find("\r\n\r\n");
    if (pos == std::string::npos) {
        throw std::invalid_argument("brocken response");
    }

    query = response.substr(0, pos);
    std::transform(query.begin(), query.end(), query.begin(),
                   [](unsigned char c) { return std::tolower(c); });
}

void HttpResponse::findCode() {
    std::string::size_type code_pos = query.find(" ");
    if (code_pos == std::string::npos) {
        throw std::invalid_argument("brocken query");
    }

    code = std::stoi(query.substr(code_pos + 1, 3));
}

void HttpResponse::findType() {
    std::string::size_type start_pos = query.find("content-type: ");
    if (start_pos == std::string::npos) {
        throw std::invalid_argument("brocken query");
    }

    start_pos += strlen("content-type: ");

    std::string::size_type end_pos = query.find(';', start_pos);

    if (query.find("text", start_pos, end_pos - start_pos)) {
        type = text;
        return;
    }

    if (query.find("image", start_pos, end_pos - start_pos)) {
        type = img;
        return;
    }

    type = other;
    return;
}

HttpResponse &HttpResponse::operator=(const HttpResponse &other) {
    query = other.query;
    type = other.type;
    contentLength = other.contentLength;
    body = new char[contentLength];
    if (body == nullptr) {
        throw std::bad_alloc();
    }
    bzero(body, contentLength);
    memcpy(body, other.body, contentLength - 1);
    code = other.code;

    return *this;
}

HttpResponse::HttpResponse(const HttpResponse &other) { *this = other; }

void HttpResponse::createBody(const char *buf) {
    // std::cout << contentLength;

    if (buf == nullptr) {
        throw std::runtime_error("empty response");
    }

    if (body != nullptr) {
        delete[] body;
    }

    body = new char[contentLength];
    if (body == nullptr) {
        throw std::bad_alloc();
    }
    bzero(body, contentLength);

    memcpy(body, buf + query.size() + strlen("\r\n\r\n"), contentLength - 1);
}

void HttpResponse::findContentLength() {
    size_t start_pos = query.find("content-length: ");
    if (start_pos == std::string::npos) {
        throw std::logic_error("no content length");
    }

    start_pos += strlen("content-length: ");

    std::string size = query.substr(start_pos, query.size() - start_pos);

    contentLength = std::stoi(size);
}

void HttpResponse::findRedirectLocation() {
    std::string::size_type start_pos = query.find("location: ");
    if (start_pos == std::string::npos) {
        throw std::invalid_argument("redirection location not found");
    }

    start_pos += strlen("location: ");

    std::string::size_type end_pos = query.find("\r\n");
    if (end_pos == std::string::npos) {
        throw std::invalid_argument("redirection location not found");
    }

    redirectLocation = query.substr(start_pos, end_pos - start_pos);

    if (redirectLocation.empty()) {
        throw std::invalid_argument("redirection location not found");
    }
}

HttpResponse::HttpResponse(const char *buf) : body(nullptr) {
    if (buf == nullptr) {
        throw std::runtime_error("empty response");
    }

    std::string response(buf, 1024);

    createQuery(response);
    findCode();
    if (code == 200) {
        findType();
        findContentLength();
        createBody(buf);
    }
}

HttpResponse::~HttpResponse() {
    if (body != nullptr) {
        delete[] body;
    }
}

void Socket::socketSettings() {
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1) {
        throw std::runtime_error("connection error: " +
                                 std::string(strerror(errno)));
    }

    int connected = ::connect(socketFd, (struct sockaddr *)&addr, sizeof(addr));
    if (connected == -1) {
        ::close(socketFd);
        throw std::runtime_error("connect error: " +
                                 std::string(strerror(errno)));
    }

    struct timeval tv;
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;
    if (setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) != 0) {
        throw std::runtime_error("rcvtimeout: " + std::string(strerror(errno)));
    }
}

Socket::Socket(const std::string &url) : request(url), response() {
    resolve(request.host);
    socketSettings();
}

Socket::~Socket() { ::close(socketFd); }

void Socket::resolve(const std::string &url) {
    size_t i = 0;
    struct hostent *hp = gethostbyname(url.c_str());

    while (i < 3 && hp == NULL) {
        hp = gethostbyname(url.c_str());
        ++i;
        sleep(TIMEOUT);
    } //если днс сервер не отвечает

    if (hp == NULL) {
        throw std::runtime_error("getting of hostent failed: " +
                                 std::string(strerror(h_errno)));
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(443);
    memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);
}

void Socket::send() { __send(); }

HttpResponse Socket::recv() {
    char *buf = __recv();
    if (buf == nullptr) {
        throw std::runtime_error("empty response");
    }

    try {
        response = HttpResponse(buf);
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    free(buf);

    return response;
}
