#include "create_new_page.hpp"
#include "http_client.hpp"
#include "parser.hpp"
#include <filesystem>

int create_new_page(const std::string &url, const std::string &path_to_dir) {
    http_client my_client(url);

    my_client.send();

    while (my_client.recieve() == REDIRECT) {
        my_client.redirect();
        my_client.send();
    }

    std::string path_to_static(path_to_dir);
    path_to_static += "/static";
    std::filesystem::create_directories(path_to_static);

    std::string path_to_html_file(path_to_dir);
    path_to_html_file += "/index.html";
    std::ofstream file(path_to_html_file);
    file << my_client.get_response();

    html_parser my_html_parser;
    my_html_parser.parse(path_to_html_file);

    int k = 0;
    std::string edit_html = my_client.get_response();
    for (std::string url : my_html_parser.sources) {
        std::cout << "\n@@@" << url << "@@@\n";

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

        std::string path_to_new_static_file(path_to_dir);
        path_to_new_static_file += "/static/";
        path_to_new_static_file += std::to_string(k++);
        std::string file_type = my_html_parser.file_type(url);
        path_to_new_static_file += file_type;

        std::ofstream static_file(path_to_new_static_file);
        static_file << my_client.get_response();
        static_file.close();

        if (my_html_parser.is_css(file_type)) {
            std::string edit_css(my_client.get_response());
            css_parser my_css_parser;
            my_css_parser.parse(path_to_new_static_file);

            for (std::string css_url : my_css_parser.sources) {
                std::cout << "\n&&&" << css_url << "&&&\n";
                std::string::size_type new_url_pos = url.find_last_of('/');
                std::string new_url = url.substr(0, new_url_pos);
                new_url += "/" + css_url;
                if (url.find("hhtp") != std::string::npos) {
                    new_url = url;
                }
                if (url.find("//") != std::string::npos) {
                    new_url = "https:" + url;
                }

                try {
                    my_client.new_request(new_url);
                } catch (std::runtime_error) {
                    continue;
                }

                my_client.send();

                enum client_exit_status css_recv = my_client.recieve();

                while (css_recv == REDIRECT) {
                    try {
                        my_client.redirect();
                    } catch (std::exception) {
                        break;
                    }
                    my_client.send();
                    try {
                        css_recv = my_client.recieve();
                    } catch (std::exception) {
                        break;
                    }
                }

                if (recv == REDIRECT) {
                    continue;
                }

                /*std::string path_to_new_css_static_file(argv[2]);
                path_to_new_css_static_file += "/static/";*/
                std::string path_to_new_css_static_file(path_to_dir);
                path_to_new_css_static_file += "/static/";
                path_to_new_css_static_file += std::to_string(k++);

                std::string css_file_type = my_css_parser.file_type(css_url);
                path_to_new_css_static_file += css_file_type;

                std::ofstream css_static_file(path_to_new_css_static_file);
                css_static_file << my_client.get_response();
                css_static_file.close();

                std::string::size_type css_src_start_pos =
                    edit_css.find(css_url);

                edit_css.erase(css_src_start_pos, css_url.size());
                path_to_new_css_static_file.erase(0, path_to_dir.size());
                path_to_new_css_static_file.erase(0, strlen("/static/"));

                edit_css.insert(css_src_start_pos, path_to_new_css_static_file);
            }

            static_file.open(path_to_new_static_file,
                             std::ios::out | std::ios::trunc);
            static_file << edit_css;
            static_file.close();
        }

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
            path_to_new_static_file.erase(0, path_to_dir.size());
            path_to_new_static_file.insert(0, ".");
            edit_html.insert(start_pos, path_to_new_static_file);
        }
    }

    file.close();

    file.open(path_to_html_file, std::ios::out | std::ios::trunc);
    file << edit_html;

    return 0;
}