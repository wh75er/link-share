#include "gtest/gtest.h"

#include "application.hpp"


TEST(RoomTest, archiveLinkTest) {
    std::string name, id, link;
    Room room(name, id);

    ASSERT_STREQ(room.archiveLink(link).c_str(), "str");
}

TEST(LinkTest, addSnapshot) {
    std::string name, url, tag;
    Link lk(name, url, tag);

    ASSERT_STREQ(lk.addSnapshot().c_str(), "str");
}
