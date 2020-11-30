#include "gtest/gtest.h"

#include "http_client.hpp"
#include "parser.hpp"

/*TEST(html_parser_test, parse_test) {
    http_client new_client("www.example.com");
    ASSERT_EQ(new_client.send("GET https://www.example.com HTTP/1.1\r\nHost: "
                              "www.example.com\r\n"),
              SUCCESS);
    std::string *path_to_file;
    ASSERT_EQ(new_client.recieve(path_to_file), SUCCESS);
    ASSERT_EQ(path_to_file->c_str(), "example.html");

    html_parser new_parser("https://www.example.com");
    ASSERT_EQ(new_parser.parse(*path_to_file), SUCCESS_PARSE);
}

TEST(html_parser_test, get_src_url_from_string_test) {
    html_parser new_parser("");
    std::string str = "<img src=";
    str += '"';
    str += "url";
    str += '"';
    str += ">";
    ASSERT_NE(new_parser.get_src_url_from_string(str), nullptr);
    ASSERT_STREQ(new_parser.get_src_url_from_string(str)->c_str(), "url");
}

TEST(html_parser_test, is_css_test) {
    html_parser new_parser("");
    std::string str = "asd.css";
    ASSERT_EQ(new_parser.is_css(str), true);
}

TEST(css_parser_test, parse_test) {
    css_parser new_parser("");
    std::string path_to_file("suorce.css");
    ASSERT_EQ(new_parser.parse(path_to_file), SUCCESS_PARSE);
}

TEST(css_parser_test, get_src_url_from_string_test) {
    css_parser new_parser("");
    std::string str = "background: url(";
    str += '"';
    str += "url";
    str += '"';
    str += ")";
    ASSERT_NE(new_parser.get_src_url_from_string(str), nullptr);
    ASSERT_STREQ(new_parser.get_src_url_from_string(str)->c_str(), "url");
}*/