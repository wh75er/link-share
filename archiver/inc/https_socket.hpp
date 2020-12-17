#include "http_socket.hpp"

#include <iostream>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <vector>

class HttpsSocket : public Socket {
public:
    HttpsSocket(const std::string &url);
    ~HttpsSocket();

    void createNewRequest(const std::string &url);

private:
    SSL *ssl;
    void SSLSettings();

    virtual void __send() override;
    virtual char *__recv(int *size) override;
};