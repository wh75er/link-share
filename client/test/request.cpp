#include "gtest/gtest.h"

#include "requestHandler.hpp"
#include <typeinfo>
#include <sstream>
#include <memory>


TEST(RequestTest, logInTest) {
    std::stringstream is;
    LogInReqHandler req;

    //ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, logOutTest) {
    std::stringstream is;
    LogOutReqHandler req;

    //ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, CreateRoomTest) {
    std::stringstream is;
    CreateRoomReqHandler req;

   // ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, RemoveRoomTest) {
    std::stringstream is;
    RemoveRoomReqHandler req;

    //ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, AddLinkTest) {
    std::stringstream is;
    AddLinkReqHandler req;

    //ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, RemoveLinkTest) {
    std::stringstream is;
    RemoveLinkReqHandler req;

   // ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, ArchiveLinkTest) {
    std::stringstream is;
    ArchiveLinkReqHandler req;

   // ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}
