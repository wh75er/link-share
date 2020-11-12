#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "room.hpp"
#include "response.hpp"
#include "handlers/signUpUserHandler.hpp"

TEST(HandlersSuit, SignUpSuccessCase) {
  User user("Test", "qwerty", "", 0);
  Response response;

  BaseHandler h = SignUpUserHandler(user, response);

  h.execute();

  EXPECT_EQ(response.getError(), SUCCESS);
}

TEST(HandlersSuit, SignUpValidationError) {
  User user("'hello'${}", "qwerty", "", 0);
  Response response;

  BaseHandler h = SignUpUserHandler(user, response);

  h.execute();

  EXPECT_NE(response.getError(), SUCCESS);
}
