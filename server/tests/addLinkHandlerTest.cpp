#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "room.hpp"
#include "response.hpp"
#include "handlers/addLinkHandler.hpp"

TEST(HandlersSuit, AddLinkSuccessCase) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("Test", "valid_token", 0),
      {});
  Response response;

  BaseHandler h = AddLinkHandler(webLink, response);

  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);
  EXPECT_EQ(response.getHasFiles(), true);
}

TEST(HandlersSuit, AddLinkHandlerAuthorizationError) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("Test", "invalid_token", 0),
      {});
  Response response;

  BaseHandler h = AddLinkHandler(webLink, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}

TEST(HandlersSuit, AddLinkHandlerUserNotExists) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("NonExistedUser", "token", 0),
      {});
  Response response;

  BaseHandler h = AddLinkHandler(webLink, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}
