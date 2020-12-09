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

    std::string path_to_unedited_html(argv[2]);
    path_to_unedited_html += "/index1.html";
    std::ofstream file(path_to_unedited_html);
    file << my_client.get_response();

    html_parser my_html_parser(argv[1]);
    my_html_parser.parse(path_to_unedited_html);

    int k = 0;
    std::string edit_html = my_client.get_response();

    for (std::string url : my_html_parser.sources) {
        try {
            my_client.new_request(url);
        } catch (std::runtime_error) {
            continue;
        }

        my_client.send();

        enum client_exit_status recv = my_client.recieve();

        while (recv == REDIRECT) {
            try {
                my_client.redirect();
            } catch (std::exception) {
                break;
            }
            my_client.send();
            try {
                recv = my_client.recieve();
            } catch (std::exception) {
                break;
            }
        }

        if (recv == REDIRECT) {
            continue;
        }

        std::string path_to_new_static_file(argv[2]);
        path_to_new_static_file += "/static/";
        path_to_new_static_file += std::to_string(k++);
        path_to_new_static_file += my_html_parser.file_type(url);
        std::ofstream static_file(path_to_new_static_file);
        static_file << my_client.get_response();

        while (true) {
            std::string::size_type start_pos = edit_html.find(url);
            if (start_pos == std::string::npos) {
                break;
                // std::cout << edit_html;
                // std::cout << '|' << url << '|' << '\n';
                // std::cout << edit_html.size() << '\n';
                // puts("wtf");
            }
            edit_html.erase(start_pos, url.size());
            std::cout << "||" << path_to_new_static_file << "||";
            path_to_new_static_file.erase(0, strlen(argv[2]));
            path_to_new_static_file.insert(0, ".");
            edit_html.insert(start_pos, path_to_new_static_file);
        }
    }

    std::string path_to_edited_html(argv[2]);
    path_to_edited_html += "/index.html";

    std::ofstream edited_file(path_to_edited_html);
    edited_file << edit_html;

    return 0;
}