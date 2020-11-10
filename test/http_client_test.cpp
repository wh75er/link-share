#include "gtest/gtest.h"
#include <string>

extern "C" {
#include "http_client.hpp"
}

TEST(http_client_test, constructor_test) { EXPECT_EQ(2, (1 + 1)); }