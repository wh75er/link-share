#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

enum parser_exit_status { SUCCESS_PARSE, FAILURE_PARSE };

class parser {
protected:
    std::string url;

public:
    std::vector<std::string> sources;
    parser(){};
    parser(const std::string &_url) : url(_url){};
    virtual bool is_source(const std::string &str) = 0;
    virtual enum parser_exit_status parse(const std::string &path_to_file) = 0;
    virtual void get_src_url_from_string(const std::string &str) = 0;
};

class html_parser : public parser {
public:
    html_parser(){};
    html_parser(const std::string &_url);
    bool is_source(const std::string &str);
    enum parser_exit_status parse(const std::string &path_to_file);
    void get_src_url_from_string(const std::string &str);
    std::string file_type(const std::string &url);
    bool is_css(const std::string &str);
};

class css_parser : public parser {
public:
    bool is_source(const std::string &str);
    explicit css_parser(const std::string &_url);
    enum parser_exit_status parse(const std::string &path_to_file);
    void get_src_url_from_string(const std::string &str);
};
