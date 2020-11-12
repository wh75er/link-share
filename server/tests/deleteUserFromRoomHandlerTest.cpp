#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "room.hpp"
#include "response.hpp"
#include "handlers/deleteUserFromRoomHandler.hpp"
#include "handlers/addUserToRoomHandler.hpp"

TEST(HandlersSuit, DeleteUserFromRoomSuccessCase) {
  Room room(1,
      {"user-1"}, 
      User("Test", "valid_token", 0)
      );
  Response response;

  BaseHandler h = AddUserToRoomHandler(room, response);

  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);

  h = DeleteUserFromRoomHandler(room, response);
  
  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);
}

TEST(HandlersSuit, DeleteUserFromRoomMultipleUsersSuccessCase) {
  Room room(1,
      {"user-1", "user-2"}, 
      User("Test", "valid_token", 0)
      );
  Response response;

  BaseHandler h = AddUserToRoomHandler(room, response);

  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);

  h = DeleteUserFromRoomHandler(room, response);
  
  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);
}

TEST(HandlersSuit, DeleteUserFromRoomBadAuthorization) {
  Room room(1,
      {"user-1"}, 
      User("Test", "valid_token", 0)
      );
  Response response;

  BaseHandler h = AddUserToRoomHandler(room, response);

  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);

  room.setUser(User("Test", "invalid_token", 0));

  h = DeleteUserFromRoomHandler(room, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}

