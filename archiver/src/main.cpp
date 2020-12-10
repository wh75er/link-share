#include "create_new_page.hpp"

int main(int argc, char **argv) {
    std::string url(argv[1]);
    std::string dir(argv[2]);
    create_new_page(url, dir);
    return 0;
}