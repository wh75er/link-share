#include "gtest/gtest.h"

#include <typeinfo>
#include "request.hpp"
#include "response.hpp"


TEST(ResponseTest, logInTest) {
    Application app;
    LogInReq req;
    LogInResp resp;

    ASSERT_EQ(resp.doLogic(req, app), RESP_SUCCESS);
}

TEST(ResponseTest, logOutTest) {
    Application app;
    LogOutReq req;
    LogOutResp resp;

    ASSERT_EQ(resp.doLogic(req, app), RESP_SUCCESS);
}

TEST(ResponseTest, CreateRoomTest) {
    Application app;
    CreateRoomReq req;
    CreateRoomResp resp;

    ASSERT_EQ(resp.doLogic(req, app), RESP_SUCCESS);
}

TEST(ResponseTest, RemoveRoomTest) {
    Application app;
    RemoveRoomReq req;
    RemoveRoomResp resp;

    ASSERT_EQ(resp.doLogic(req, app), RESP_SUCCESS);
}

TEST(ResponseTest, AddLinkTest) {
    Application app;
    AddLinkReq req;
    AddLinkResp resp;

    ASSERT_EQ(resp.doLogic(req, app), RESP_SUCCESS);
}

TEST(ResponseTest, RemoveLinkTest) {
    Application app;
    RemoveLinkReq req;
    RemoveLinkResp resp;

    ASSERT_EQ(resp.doLogic(req, app), RESP_SUCCESS);
}

TEST(ResponseTest, ArchiveLinkTest) {
    Application app;
    ArchiveLinkReq req;
    ArchiveLinkResp resp;

    ASSERT_EQ(resp.doLogic(req, app), RESP_SUCCESS);
}

TEST(ResponseTest, ResponseHandlerTest) {
    std::string str;
    ResponseHandler handler;

    ASSERT_EQ(typeid(handler.HandleInput(str)), typeid(std::shared_ptr<Response>));
}

