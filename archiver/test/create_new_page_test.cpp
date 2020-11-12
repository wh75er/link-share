#include "gtest/gtest.h"

#include "create_new_page.hpp"

TEST(create_new_page_test, creation_test) {
    ASSERT_EQ(create_new_page("www.example.com"), "example_dir");
}
