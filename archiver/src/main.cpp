//#include "create_new_page.hpp"
#include "https_socket.hpp"
#include <fstream>

int main(int argc, char **argv) {
    /*std::string url(argv[1]);
    std::string dir(argv[2]);
    create_new_page(url, dir);*/
    HttpsSocket my_sock(
        "https://yastatic.net/s3/home/logos/share/share-logo_ru.png");

    my_sock.send();
    HttpResponse mk = my_sock.recv();

    std::ofstream file("some.png", std::ios::binary);
    file.write(mk.body, 2746);
    file.close();

    // std::cout << mk.query.size() << "|||\n";
    // std::cout << mk.query;

    return 0;
}
