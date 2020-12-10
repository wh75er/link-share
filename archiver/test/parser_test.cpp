#include "gtest/gtest.h"

#include "parser.hpp"
#include <fstream>

TEST(html_parser_test, parse_test) {
    puts("\ng\n");
    std::string path_to_file("parse_test_file.txt");
    std::ofstream file(path_to_file);
    assert(file);
    file << "<div>Some text</div>"
            "<img src=\"img/src.png\">"
            "<link href=\"https://style.css\">";
    file.close();
    html_parser my_html_parser;
    my_html_parser.parse(path_to_file);

    EXPECT_EQ(my_html_parser.sources[0], "img/src.png");
    EXPECT_EQ(my_html_parser.sources[1], "https://style.css");
}
