#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

enum parser_exit_status { SUCCESS, FAILURE };

class parser {
    std::vector<std::string> sources;
    std::string url;

public:
    virtual ~parser() = 0;
    virtual enum parser_exit_status parse(const std::string &path_to_file) = 0;
    virtual std::string &get_src_url_from_string(const std::string &str) = 0;
};

class html_parser : public parser {
public:
    enum parser_exit_status parse(const std::string &path_to_file);
    std::string &get_src_url_from_string(const std::string &str);
    const std::string &type_of_src(const std::string &str);
};

class css_parser : public parser {
public:
    enum parser_exit_status parse(const std::string &path_to_file);
    std::string &get_src_url_from_string(const std::string &str);
};
