#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <vector>


class parser {
public:
    std::vector<std::string> sources;
    parser(){};
    virtual bool is_source(const std::string &str) = 0;
    virtual void parse(const std::string &path_to_file) = 0;
    virtual void get_src_url_from_string(const std::string &str) = 0;
};

class html_parser : public parser {
public:
    html_parser(){};
    bool is_source(const std::string &str);
    void parse(const std::string &path_to_file);
    void get_src_url_from_string(const std::string &str);
    std::string file_type(const std::string &url);
    bool is_css(const std::string &str);
};

class css_parser : public parser {
public:
    css_parser(){};
    bool is_source(const std::string &str);
    explicit css_parser(const std::string &_url);
    std::string file_type(const std::string &url);
    void parse(const std::string &path_to_file);
    void get_src_url_from_string(const std::string &str);
};
