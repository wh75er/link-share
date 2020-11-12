#include "gtest/gtest.h"

#include "request.hpp"
#include <typeinfo>
#include <sstream>
#include <memory>


TEST(RequestTest, logInTest) {
    std::stringstream is;
    LogInReq req;

    ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, logOutTest) {
    std::stringstream is;
    LogOutReq req;

    ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, CreateRoomTest) {
    std::stringstream is;
    CreateRoomReq req;

    ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, RemoveRoomTest) {
    std::stringstream is;
    RemoveRoomReq req;

    ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, AddLinkTest) {
    std::stringstream is;
    AddLinkReq req;

    ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, RemoveLinkTest) {
    std::stringstream is;
    RemoveLinkReq req;

    ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, ArchiveLinkTest) {
    std::stringstream is;
    ArchiveLinkReq req;

    ASSERT_EQ(req.buildRequestFromInput(is), REQ_SUCCESS);
}

TEST(RequestTest, RequestHandlerTest) {
    std::string str;
    RequestHandler handler;

    ASSERT_EQ(typeid(handler.HandleInput(str)), typeid(std::shared_ptr<Request>));
}
