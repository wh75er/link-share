#include "gtest/gtest.h"

#include "http_client.hpp"
#include "parser.hpp"

TEST(html_parser_test, parse_test_1) {
    html_parser new_parser;
    ASSERT_EQ(new_parser.parse("asd"), FAILURE_PARSE);
}

TEST(html_parser_test, parse_test_2) {
    http_client new_client;
    ASSERT_EQ(new_client.send("GET https://www.example.com HTTP/1.1\r\nHost: "
                              "www.example.com\r\n"),
              SUCCESS);
    std::string *path_to_file;
    ASSERT_EQ(new_client.recieve(path_to_file), SUCCESS);
    ASSERT_EQ(path_to_file->c_str(), "example.html");

    html_parser new_parser;
    ASSERT_EQ(new_parser.parse(*path_to_file), SUCCESS_PARSE);
}

TEST(html_parser_test, get_src_url_from_string_test_1) {
    html_parser new_parser;
    std::string str = "<img src=";
    str += '"';
    str += "url";
    str += '"';
    str += ">";
    ASSERT_STREQ(new_parser.get_src_url_from_string(str).c_str(), "url");
}

TEST(html_parser_test, get_src_url_from_string_test_2) {
    html_parser new_parser;
    std::string str = "sdf";
    ASSERT_STREQ(new_parser.get_src_url_from_string(str).c_str(), "\0");
}

TEST(html_parser_test, type_of_src_test_1) {
    html_parser new_parser;
    std::string str = "asd.css";
    ASSERT_EQ(new_parser.is_css(str), true);
}

TEST(html_parser_test, type_of_src_test_2) {
    html_parser new_parser;
    std::string str = "asd.png";
    ASSERT_EQ(new_parser.is_css(str), false);
}