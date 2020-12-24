#include <cstring>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

class parser {
public:
    std::vector<std::string> sources;
    parser(){};
    virtual bool is_source(const std::string &str) = 0;
    virtual void parse(const std::string &path_to_file) = 0;
    virtual void get_src_url_from_string(const std::string &str) = 0;
};

class HtmlParser : public parser {
public:
    HtmlParser(){};
    bool is_source(const std::string &str);
    void parse(const std::string &path_to_file);
    void get_src_url_from_string(const std::string &str);
    std::string file_type(const std::string &url);
    bool is_css(const std::string &str);
};

class CssParser : public parser {
public:
    CssParser(){};
    bool is_source(const std::string &str);
    std::string file_type(const std::string &url);
    void parse(const std::string &path_to_file);
    void get_src_url_from_string(const std::string &str);
};
