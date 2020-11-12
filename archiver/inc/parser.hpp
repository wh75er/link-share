#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

enum parser_exit_status { SUCCESS_PARSE, FAILURE_PARSE };

class parser {
    std::vector<std::string> sources;
    std::string url;

public:
    virtual enum parser_exit_status parse(const std::string &path_to_file) = 0;
    virtual std::string get_src_url_from_string(const std::string &str) = 0;
};

class html_parser : public parser {
public:
    enum parser_exit_status parse(const std::string &path_to_file);
    std::string get_src_url_from_string(const std::string &str);
    bool is_css(const std::string &str);
};

class css_parser : public parser {
public:
    enum parser_exit_status parse(const std::string &path_to_file);
    std::string get_src_url_from_string(const std::string &str);
};
