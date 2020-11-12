#include "parser.hpp"

parser_exit_status html_parser::parse(const std::string &path_to_file) {
    return SUCCESS_PARSE;
}

std::string *html_parser::get_src_url_from_string(const std::string &str) {
    return nullptr;
}

bool html_parser::is_css(const std::string &str) { return false; }

parser_exit_status css_parser::parse(const std::string &path_to_file) {
    return FAILURE_PARSE;
}

std::string *css_parser::get_src_url_from_string(const std::string &str) {
    return nullptr;
}
