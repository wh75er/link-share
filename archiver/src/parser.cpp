#include "parser.hpp"
#include <fstream>

bool is_file(const std::string &str) {
    std::string::size_type src_url_start_pos = str.find('"');
    if (src_url_start_pos == std::string::npos) {
        src_url_start_pos = str.find_last_of("'");
    }
    if (src_url_start_pos != std::string::npos) {
        std::string::size_type src_url_end_pos =
            str.find('"', src_url_start_pos + 1);
        if (src_url_end_pos == std::string::npos) {
            src_url_end_pos = str.find("'", src_url_start_pos + 1);
        }
        if (src_url_end_pos == std::string::npos) {
            return false;
        }
        std::string buf =
            str.substr(src_url_start_pos, src_url_end_pos - src_url_start_pos);
        std::string::size_type src_format_start_pos = buf.find_last_of(".");
        if (src_format_start_pos == std::string::npos) {
            return false;
        }
        std::string format =
            buf.substr(src_format_start_pos, buf.size() - src_format_start_pos);
        if (format.find("/") == std::string::npos) {
            return true;
        }
    }

    return false;
}

bool html_parser::is_css(const std::string &str) {
    if (str.find(".css") != std::string::npos) {
        return true;
    }

    return false;
}

std::string html_parser::file_type(const std::string &url) {
    std::string::size_type last_pos = url.find_last_of('/');
    if (last_pos == std::string::npos) {
        last_pos = 0;
    }
    std::string buf = url.substr(last_pos, url.size() - last_pos);
    std::string::size_type format_start_pos = buf.find('.');
    std::string format =
        buf.substr(format_start_pos, buf.size() - format_start_pos);

    return format;
}

bool html_parser::is_source(const std::string &str) {
    std::string::size_type src_start_pos = str.find("<LINK");
    if (src_start_pos == std::string::npos) {
        src_start_pos = str.find("<link");
    }
    if (src_start_pos != std::string::npos) {
        src_start_pos = str.find("href=");
        if (src_start_pos != std::string::npos) {
            src_start_pos += strlen("href=");
            if (is_file(
                    str.substr(src_start_pos, str.size() - src_start_pos))) {
                return true;
            }
        }
    }

    src_start_pos = str.find("src=");
    if (src_start_pos != std::string::npos) {
        if (is_file(str.substr(src_start_pos, str.size() - src_start_pos))) {
            return true;
        }
    }

    return false;
}

void html_parser::parse(const std::string &path_to_file) {
    std::ifstream html_file(path_to_file);
    if (!html_file) {
        html_file.close();
        throw std::invalid_argument("file error");
    }
    std::string src_string;

    while (!html_file.eof()) {
        std::getline(html_file, src_string, '>');
        if (is_source(src_string)) {
            get_src_url_from_string(src_string);
        }
    }

    html_file.close();
}

void html_parser::get_src_url_from_string(const std::string &str) {
    std::string::size_type url_start_pos = str.find("href=");
    if (url_start_pos != std::string::npos) {
        url_start_pos += strlen("href=\"");
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
        url_start_pos += strlen("src=\"");
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

void css_parser::parse(const std::string &path_to_file) {
    std::ifstream css_file(path_to_file);
    if (!css_file) {
        throw std::invalid_argument("file error");
    }

    std::string src_string;
    while (!css_file.eof()) {
        std::getline(css_file, src_string, ';');
        if (is_source(src_string)) {
            get_src_url_from_string(src_string);
        }
    }
}

bool css_parser::is_source(const std::string &str) {
    std::string::size_type url_start_pos = str.find("src:");
    if (url_start_pos != std::string::npos) {
        url_start_pos = str.find("url(", url_start_pos);
        if (url_start_pos != std::string::npos) {
            return true;
        }
    }
    return false;
}

void css_parser::get_src_url_from_string(const std::string &str) {
    std::string::size_type src_start_pos = str.find("url(");
    if (src_start_pos != std::string::npos) {
        src_start_pos += strlen("url(");
        if (str[src_start_pos] == '"' || str[src_start_pos] == '\'') {
            ++src_start_pos;
            std::string::size_type src_end_pos = str.find('"', src_start_pos);
            if (src_end_pos == std::string::npos) {
                std::string::size_type src_end_pos =
                    str.find('\'', src_start_pos);
            }
            std::string url =
                str.substr(src_start_pos, src_end_pos - src_start_pos);
            sources.push_back(url);

        } else {
            std::string::size_type src_end_pos = str.find(')', src_start_pos);
            if (src_end_pos != std::string::npos) {
                std::string url =
                    str.substr(src_start_pos, src_end_pos - src_start_pos);
                sources.push_back(url);
            }
        }
    }
    return;
}

std::string css_parser::file_type(const std::string &url) {
    std::string::size_type type_start_pos = url.find_last_of('.');
    if (type_start_pos == std::string::npos) {
        throw std::runtime_error("invalid url");
    }
    return url.substr(type_start_pos, url.size() - type_start_pos);
}
