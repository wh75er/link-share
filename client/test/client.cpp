#include "gtest/gtest.h"

#include <typeinfo>
#include "client.hpp"
#include "socket.hpp"



TEST(ClientTest, ReadFromServerTest) {
    Client client;

    ASSERT_EQ(client.readFromServer(), "str");
}
