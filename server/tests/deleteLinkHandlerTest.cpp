#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "room.hpp"
#include "response.hpp"
#include "handlers/deleteLinkHandler.hpp"
#include "handlers/addLinkHandler.hpp"

TEST(HandlersSuit, DeleteLinkSuccessCase) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("Test", "valid_token", 0),
      {});
  Response response;

  BaseHandler h = AddLinkHandler(webLink, response);

  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);

  h = DeleteLinkHandler(webLink, response);

  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);
}

TEST(HandlersSuit, DeleteLinkHandlerAuthorizationError) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("Test", "valid_token", 0),
      {});
  Response response;

  BaseHandler h = AddLinkHandler(webLink, response);

  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);

  webLink.setUser(User("Test", "invalid_token", 0));

  h = DeleteLinkHandler(webLink, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}

TEST(HandlersSuit, DeleteLinkHandlerUserNotExists) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("NonExistedUser", "token", 0),
      {});
  Response response;

  BaseHandler h = DeleteLinkHandler(webLink, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}
