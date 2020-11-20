#include "gtest/gtest.h"

#include "http_client.hpp"

TEST(http_client, create_request_test) {
    http_client new_client("www.any.com");
    new_client.connect();
    std::string request =
        new_client.create_request("https://www.any.com/something");
    ASSERT_STREQ(
        "GET https://www.any.com/something HTTP/1.1\r\nHost: www.any.com\r\n",
        request.c_str());
}

TEST(http_client, send_test_1) {
    http_client new_client("ASD");
    new_client.connect();
    ASSERT_EQ(new_client.send("asd"), BAD_REQUEST_ERROR);
}

TEST(http_client, send_test_2) {
    http_client new_client("www.example.com");
    new_client.connect();
    ASSERT_EQ(new_client.send("GET https://www.example.com HTTP/1.1\r\nHost: "
                              "www.example.com\r\n"),
              SUCCESS);
}

TEST(http_client, recieve_test) {
    http_client new_client("www.example.com");
    new_client.connect();
    ASSERT_EQ(new_client.send("GET https://www.example.com HTTP/1.1\r\nHost: "
                              "www.example.com\r\n"),
              SUCCESS);
    std::string *path_to_file;
    ASSERT_EQ(new_client.recieve(path_to_file), SUCCESS);
    ASSERT_EQ(path_to_file->c_str(), "example.html");
}

TEST(http_client, connect_test) {
    http_client new_client("www.example.com");
    ASSERT_EQ(new_client.connect(), SUCCESS);
}