#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "room.hpp"
#include "response.hpp"
#include "handlers/addUserToRoomHandler.hpp"

TEST(HandlersSuit, AddUserToRoomSuccessCase) {
  Room room(1,
      {"user-1"}, 
      User("Test", "valid_token", 0)
      );
  Response response;

  BaseHandler h = AddUserToRoomHandler(room, response);
  
  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);
}

TEST(HandlersSuit, AddUserToRoomMultipleUsersSuccessCase) {
  Room room(1,
      {"user-1", "user-2"}, 
      User("Test", "valid_token", 0)
      );
  Response response;

  BaseHandler h = AddUserToRoomHandler(room, response);
  
  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);
}

TEST(HandlersSuit, AddUserToRoomBadAuthorization) {
  Room room(1,
      {"user-1"}, 
      User("Test", "invalid_token", 0)
      );
  Response response;

  BaseHandler h = AddUserToRoomHandler(room, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}

TEST(HandlersSuit, AddUserToRoomMainUserNotExists) {
  Room room(1,
      {"user-1"}, 
      User("NonExistingUser", "token", 0)
      );
  Response response;

  BaseHandler h = AddUserToRoomHandler(room, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}

TEST(HandlersSuit, AddUserToRoomAddedUserNotExists) {
  Room room(1,
      {"NonExistingUser"}, 
      User("Test", "valid_token", 0)
      );
  Response response;

  BaseHandler h = AddUserToRoomHandler(room, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}
