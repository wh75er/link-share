#include "parser.hpp"
#include <fstream>

html_parser::html_parser(const std::string &_url) : parser(_url){};

bool is_file(const std::string &str) {
    //проверяет имеет ли ресурс расширение(ищет точку
    //и проверяте что после нее нет '/')
    std::string::size_type src_format = str.find_last_of('.');
    if (src_format != std::string::npos) {
        if (str.find('/', src_format) == -1) {
            return true;
        }
    }

    return false;
}

bool html_parser::is_source(const std::string &str) {
    if (str.find("<link") != std::string::npos) {
        std::string::size_type src_start_pos = str.find("href=");
        if (src_start_pos != std::string::npos) {
            src_start_pos += strlen("href=");
            if (is_file(
                    str.substr(src_start_pos, str.size() - src_start_pos))) {
                return true;
            }
        }
    }

    std::string::size_type src_start_pos = str.find("src=");
    if (src_start_pos != std::string::npos) {
        if (is_file(str.substr(src_start_pos, str.size() - src_start_pos))) {
            return true;
        }
    }

    return false;
}

parser_exit_status html_parser::parse(const std::string &path_to_file) {
    std::ifstream html_file(path_to_file);
    if (!html_file) {
        throw std::invalid_argument("file error");
        return FAILURE_PARSE;
    }
    std::string src_string;

    while (!html_file.eof()) {
        // html_file >> src_string;
        std::getline(html_file, src_string, '>');
        if (is_source(src_string)) {
            puts("...............");
            // std::cout << src_string << "\n";
            // puts("\t");

            get_src_url_from_string(src_string);
            std::cout << "url: " << sources.back() << '\n';
        }
    }

    return SUCCESS_PARSE;
}

void html_parser::get_src_url_from_string(const std::string &str) {
    std::string::size_type url_start_pos = str.find("href=");
    if (url_start_pos != std::string::npos) {
        url_start_pos += strlen("href=") + 1;
        //как тада засунуть кавычку href=" пока не придумал
        //поэтмоу просто +1
        std::string::size_type url_end_pos = str.find('"', url_start_pos);
        if (url_end_pos == std::string::npos) {
            url_end_pos = str.find("'", url_start_pos);
            if (url_end_pos == std::string::npos) {
                throw std::invalid_argument("url not found");
            }
        }
        std::string url =
            str.substr(url_start_pos, url_end_pos - url_start_pos);

        sources.push_back(url);
        return;
    }

    url_start_pos = str.find("src=");
    if (url_start_pos != std::string::npos) {
        url_start_pos += strlen("src=") + 1;
        //как тада засунуть кавычку href=" пока не придумал
        //поэтмоу просто +1
        std::string::size_type url_end_pos = str.find('"', url_start_pos);
        if (url_end_pos == std::string::npos) {
            url_end_pos = str.find("'", url_start_pos);
            if (url_end_pos == std::string::npos) {
                throw std::invalid_argument("url not found");
            }
        }
        std::string url =
            str.substr(url_start_pos, url_end_pos - url_start_pos);

        sources.push_back(url);
        return;
    }

    if (url_start_pos == std::string::npos) {
        throw std::invalid_argument("url not found");
    }

    return;
}

bool html_parser::is_css(const std::string &str) { return false; }

parser_exit_status css_parser::parse(const std::string &path_to_file) {
    return FAILURE_PARSE;
}

void css_parser::get_src_url_from_string(const std::string &str) { return; }
