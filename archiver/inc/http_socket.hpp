#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

enum contentType { text, img, other };

struct HttpRequest {
    HttpRequest() : query("\0"), host("\0"){};
    HttpRequest(const std::string &url);
    std::string query;
    std::string host;

    void createQuery(const std::string &url);
    void findHost(const std::string &url);
};

struct HttpResponse {
    HttpResponse() : body(nullptr){};

    HttpResponse &operator=(const HttpResponse &other);
    HttpResponse(const HttpResponse &other);

    HttpResponse(const char *buf, const int size);

    ~HttpResponse();

    std::string query;
    enum contentType type;
    char *body;
    size_t code;
    int contentLength;
    std::string redirectLocation;

    void createQuery(const std::string &response);
    void findType();
    void findCode();
    void findContentLength(const int size);
    void createBody(const char *buf);

    void findRedirectLocation();
};

class Socket {
public:
    Socket(const std::string &url);
    ~Socket();
    void send();
    HttpResponse recv();

protected:
    int socketFd;
    void socketSettings();

    struct sockaddr_in addr;
    void resolve(const std::string &url);

    virtual void __send() = 0;
    virtual char *__recv(int *size) = 0;

    int getLength(const void *buf);

    HttpRequest request;
    HttpResponse response;
};
