
#include "gtest/gtest.h"

#include "socket.hpp"


TEST(SocketTest, RecvTest) {
    Socket sock;

    ASSERT_STREQ(sock.recv().c_str(), "str");
}