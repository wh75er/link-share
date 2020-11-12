#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "room.hpp"
#include "response.hpp"
#include "handlers/deleteRoomHandler.hpp"

TEST(HandlersSuit, DeleteRoomSuccessCase) {
  Room room(1,
      std::vector<std::string>(), 
      User("Test", "valid_token", 0)
      );
  Response response;

  BaseHandler h = DeleteRoomHandler(room, response);
  
  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);
}

TEST(HandlersSuit, DeleteRoomBadAuthorization) {
  Room room(1,
      std::vector<std::string>(), 
      User("Test", "invalid_token", 0)
      );
  Response response;

  BaseHandler h = DeleteRoomHandler(room, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}

TEST(HandlersSuit, DeleteRoomUserNotExists) {
  Room room(1,
      std::vector<std::string>(), 
      User("NonExistingUser", "token", 0)
      );
  Response response;

  BaseHandler h = DeleteRoomHandler(room, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}
