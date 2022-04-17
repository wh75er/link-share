#include "http_socket.hpp"

#include <iostream>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <vector>

class HttpsSocket : public Socket {
public:
    HttpsSocket(const std::string &url);
    ~HttpsSocket();

    void createNewRequest(const std::string &url, const std::string &main_host);

    HttpResponse handleRedirect();

private:
    SSL *ssl;
    void SSLSettings();

    virtual void sendPacket() override;
    virtual char *recvPacket(int *size) override;
};