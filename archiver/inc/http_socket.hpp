#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

std::string findUrlHost(const std::string &url);

struct HttpRequest {
    HttpRequest() : query("\0"), host("\0"){};
    HttpRequest(const std::string &url);
    HttpRequest &operator=(const HttpRequest &other);
    HttpRequest(const HttpRequest &other);

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
    std::string contentType;
    char *body;
    size_t code;
    size_t contentLength;
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
    virtual ~Socket() = 0;
    void send();
    HttpResponse recv();

protected:
    int socketFd;
    void socketSettings();

    struct sockaddr_in addr;
    void resolve(const std::string &url);

    virtual void sendPacket() = 0;
    virtual char *recvPacket(int *size) = 0;

    int getLength(const void *buf);

    HttpRequest request;
    HttpResponse response;
};
