#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "room.hpp"
#include "response.hpp"
#include "handlers/createSnapshotHandler.hpp"

TEST(HandlersSuit, GetSnapshotSuccessCase) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("Test", "valid_token", 0),
      {});
  Response response;

  BaseHandler h = CreateSnapshotHandler(webLink, response);

  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);
  EXPECT_EQ(response.getHasFiles(), true);
}

TEST(HandlersSuit, GetSnapshotHandlerAuthorizationError) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("Test", "invalid_token", 0),
      {});
  Response response;

  BaseHandler h = CreateSnapshotHandler(webLink, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}

TEST(HandlersSuit, GetSnapshotHandlerUserNotExists) {
  WebLink webLink("www.ifconfig.me",
      "1",
      User("NonExistedUser", "token", 0),
      {});
  Response response;

  BaseHandler h = CreateSnapshotHandler(webLink, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}
