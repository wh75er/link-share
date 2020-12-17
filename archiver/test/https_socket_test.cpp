#include "gtest/gtest.h"

#include "https_socket.hpp"

#include <fstream>

TEST(https_socket, constructor_test) {
    ASSERT_NO_THROW(HttpsSocket("http://www.example.com/"));
}

TEST(https_socket, send_recv_test_no_exceptions) {
    HttpsSocket my_socket("http://www.example.com/");
    ASSERT_NO_THROW(my_socket.send());
    ASSERT_NO_THROW(my_socket.recv());
}

TEST(https_socket, send_recv_text_test) {
    HttpsSocket my_socket("http://www.example.com/");
    my_socket.send();
    HttpResponse new_response = my_socket.recv();

    std::ifstream file("../test/file1.tst");

    char *test_file = new char[new_response.contentLength];

    bzero(test_file, new_response.contentLength);

    file.read(test_file, new_response.contentLength - 1);
    EXPECT_STREQ(test_file, new_response.body);

    delete[] test_file;

    file.close();
}

TEST(https_socket, send_recv_image_test) {
    HttpsSocket my_socket(
        "https://limg.imgsmail.ru/splash/v/i/share-fp-a2954bf3df.png");
    my_socket.send();
    HttpResponse new_response = my_socket.recv();

    std::ifstream file("../test/file2.png", std::ios::binary);

    char *test_file = new char[new_response.contentLength];

    file.read(test_file, new_response.contentLength);
    EXPECT_STREQ(test_file, new_response.body);

    delete[] test_file;

    file.close();
}

TEST(https_socket, redirect_test) {
    HttpsSocket my_socket("https://park.mail.ru/feed/");
    my_socket.send();
    HttpResponse new_response = my_socket.recv();

    EXPECT_EQ(new_response.code, 302);
}