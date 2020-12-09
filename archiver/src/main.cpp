#include "http_client.hpp"
#include "parser.hpp"
#include <filesystem>

/*const std::string make_source_path(const std::string &url,
                                   const std::string &dir) {
    if (url[0] == '/') {
        return dir + url.substr(1, url.size() - 1);
    }

    if (url[0] == './') {
        return dir + '/' + url.substr(strlen("./"), url.size() - strlen("./"));
    }

    std::string::size_type pos = url.find("../");
    if (pos != std::string::npos) {
        std::string new_url(url);
        while (pos != std::string::npos) {
            new_url = url.substr(strlen("../"), url.size() - strlen("../"));
        }
        return dir + '/' + new_url;
    }

    pos = url.find("http");
    if(pos!=)
}*/

int main(int argc, char **argv) {
    http_client my_client(argv[1]);

    my_client.send();

    while (my_client.recieve() == REDIRECT) {
        my_client.redirect();
        my_client.send();
    }

    std::string path_to_static(argv[2]);
    path_to_static += "/static";
    std::filesystem::create_directories(path_to_static);

    std::string path_to_html(argv[2]);
    path_to_html += "/index.html";
    std::ofstream file(path_to_html);
    file << my_client.get_response();

    html_parser my_html_parser(argv[1]);
    my_html_parser.parse(path_to_html);

    puts("1");

    int k = 0;

    for (std::string url : my_html_parser.sources) {
        try {
            my_client.new_request(url);
        } catch (std::runtime_error) {
            continue;
        }

        puts("2");

        my_client.send();

        puts("3");

        enum client_exit_status recv = my_client.recieve();

        while (recv == REDIRECT) {
            puts("4");
            try {
                my_client.redirect();
            } catch (std::runtime_error) {
                break;
            }
            my_client.send();
            recv = my_client.recieve();
            puts("5");
        }

        if (recv == REDIRECT) {
            continue;
        }

        puts("6");
        std::string path_to_new_static_file("saving/static/");
        path_to_new_static_file += std::to_string(k++);
        path_to_new_static_file += my_html_parser.file_type(url);
        std::cout << "\n||||" << path_to_new_static_file << "\n";
        std::ofstream static_file(path_to_new_static_file);
        static_file << my_client.get_response();
    }

    return 0;
}