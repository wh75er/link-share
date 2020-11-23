#include "http_client.hpp"

int main() {
    http_client my_client("https://www.tutu.ru/rasp.php?st1=8202&st2=9702&date=all");
    my_client.connect();
    my_client.send();
    std::string *recv;
    my_client.recieve(recv);
    return 0;
}