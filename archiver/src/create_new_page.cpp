#include "https_socket.hpp"
#include "parser.cpp"
#include <filesystem>
#include <fstream>

void save_file(const size_t size, const char *body,
               const std::string &file_name, const std::string &path_to_dir) {
    if (body == nullptr) {
        return;
    }

    std::string path_to_new_static_file(path_to_dir);
    path_to_new_static_file += file_name;

    std::string::size_type end_pos = path_to_new_static_file.find_last_of("?");
    if (end_pos != std::string::npos) {
        path_to_new_static_file = path_to_new_static_file.substr(0, end_pos);
    }

    std::ofstream file(path_to_new_static_file, std::ios::binary);
    file.write(body, size);
}

int create_new_page(const std::string &new_page_url,
                    const std::string &path_to_dir) {
    std::string main_host = findUrlHost(new_page_url);

    HttpsSocket my_socket(new_page_url);

    my_socket.send();
    HttpResponse new_response = my_socket.recv();

    if (new_response.code >= 300 && new_response.code < 400) {
        new_response = my_socket.handleRedirect();
    }

    std::string main_dir(path_to_dir);

    std::filesystem::create_directories(main_dir);

    std::string static_dir = main_dir + "/static";
    std::filesystem::create_directories(static_dir);

    std::string::size_type file_type_pos = new_response.contentType.find('/');

    std::string filename =
        main_dir + "/index." +
        new_response.contentType.substr(
            file_type_pos + 1, new_response.contentType.size() - file_type_pos);

    std::ofstream file(filename, std::ios::binary);
    file.write(new_response.body, new_response.contentLength);
    file.close();
    std::string index_file_str(new_response.body);

    if (filename.find("html") == std::string::npos) {
        return 0;
    }

    HtmlParser my_parser;
    my_parser.parse(filename);

    for (auto url : my_parser.sources) {
        my_socket.createNewRequest(url, main_host);
        my_socket.send();
        new_response = my_socket.recv();

        if (new_response.code == 404) {
            continue;
        }

        if (new_response.code >= 300 && new_response.code < 400) {
            new_response = my_socket.handleRedirect();
        }

        std::string::size_type src_name_start = url.find_last_of('/');
        if (src_name_start == std::string::npos) {
            src_name_start = 0;
        }

        std::string src_name =
            url.substr(src_name_start, url.size() - src_name_start);

        std::string::size_type src_name_end = src_name.find_first_of("+?");
        if (src_name_end != std::string::npos) {
            src_name = src_name.substr(0, src_name_end);
        }

        std::string::size_type start_pos = 0;

        while (true) {
            start_pos = index_file_str.find(url, start_pos);
            if (start_pos == std::string::npos) {
                break;
            }
            index_file_str.erase(start_pos, url.size());
            std::string input_name = "static" + src_name;

            index_file_str.insert(start_pos, input_name);
            start_pos += input_name.size();
        }

        save_file(new_response.contentLength, new_response.body, src_name,
                  static_dir);

        if (new_response.contentType.find("css") != std::string::npos) {
            std::string css_file_str(new_response.body);
            CssParser my_css_parser;
            my_css_parser.parse(main_dir + "/static" + src_name);
            for (auto css_url : my_css_parser.sources) {
                std::string buf_url;
                if (url.compare(0, 5, css_url, 0, 5) != 0) {
                    if (css_url.find("//") == std::string::npos &&
                        css_url.find("http") == std::string::npos) {
                        std::string::size_type cur_src_dir =
                            url.find_last_of('/');
                        if (cur_src_dir != std::string::npos) {
                            buf_url = url.substr(0, cur_src_dir);
                        }
                    }
                }

              if (buf_url.back() != '/' && css_url.front() != '/' &&
                    !buf_url.empty()) {
                    buf_url += '/';
                }

                my_socket.createNewRequest(buf_url + css_url, main_host);
                my_socket.send();
                new_response = my_socket.recv();

                if (new_response.code == 404) {
                    continue;
                }

                if (new_response.code >= 300 && new_response.code < 400) {
                    new_response = my_socket.handleRedirect();
                }

                src_name_start = css_url.find_last_of('/');
                if (src_name_start == std::string::npos) {
                    src_name_start = 0;
                }

                std::string css_src_name = css_url.substr(
                    src_name_start, css_url.size() - src_name_start);

                start_pos = 0;

                while (true) {
                    start_pos = css_file_str.find(css_url, start_pos);
                    if (start_pos == std::string::npos) {
                        break;
                    }
                    css_file_str.erase(start_pos, css_url.size());
                    std::string input_name_css = css_src_name;
                    if (input_name_css[0] == '/') {
                        input_name_css.erase(0, 1);
                    }

                    css_file_str.insert(start_pos, input_name_css);
                    start_pos += input_name_css.size();
                }
                save_file(new_response.contentLength, new_response.body,
                          css_src_name, static_dir);
            }
            save_file(css_file_str.size(), css_file_str.c_str(), src_name,
                      static_dir);

            std::ofstream edited(main_dir + "/index2.html");
            edited << index_file_str;
        }
    }

    return 0;
}
