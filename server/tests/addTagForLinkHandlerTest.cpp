#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "room.hpp"
#include "response.hpp"
#include "handlers/addTagForLinkHandler.hpp"

TEST(HandlersSuit, AddTagForLinkSuccessCase) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("Test", "valid_token", 0),
      {"tag-1"});
  Response response;

  BaseHandler h = AddTagForLinkHandler(webLink, response);

  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);
}

TEST(HandlersSuit, AddTagForLinkHandlerAuthorizationError) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("Test", "invalid_token", 0),
      {"tag-1"});
  Response response;

  BaseHandler h = AddTagForLinkHandler(webLink, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}

TEST(HandlersSuit, AddTagForLinkHandlerUserNotExists) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("NonExistedUser", "token", 0),
      {"tag-1"});
  Response response;

  BaseHandler h = AddTagForLinkHandler(webLink, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}
