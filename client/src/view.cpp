#include "view.hpp"
#include "utils.h"
#include "inputUtils.hpp"
#include <iostream>

IView::~IView() {}


enum RequestCommand {
  CREATE_ROOM,
  DELETE_ROOM,
  ADD_USERS,
  DELETE_USERS,
  ADD_LINK,
  DELETE_LINK,
  MAKE_SNAPSHOT,
  LOG_IN_USER,
  SIGN_UP_USER,
};


std::string ConsoleView::GetRequest() {
    PrintCommands();

    std::string inputStr(""), appendStr(" ");
    int key = 0;
    std::cin >> key;
    switch (key) {
    case CREATE_ROOM: {
        std::cout << "Write name and host of room" << std::endl;
        inputStr = createRoomInput();
    }
        break;
    case DELETE_ROOM: {
        std::cout << "Write name and host of room" << std::endl;
        inputStr = deleteRoomInput();
    }
        break;
    case ADD_USERS: {
        std::cout << "Write amount of users and list of users" << std::endl;
        inputStr = addUsersInput();
    }
        break;
    case DELETE_USERS: {
        std::cout << "Write amount of users and list of users" << std::endl;
        inputStr = deleteUsersInput();
    }
        break;
    case ADD_LINK: {
        std::cout << "Write name and url of link" << std::endl;
        inputStr = addLinkInput();
        break;
    }
    case DELETE_LINK: {
        std::cout << "Write name of link" << std::endl;
        inputStr = deleteLinkInput();
        break;
    }
    case MAKE_SNAPSHOT: {
        std::cout << "Write name of link" << std::endl;
        inputStr = makeSnapshotInput();
        break;
    }
    case LOG_IN_USER: {
        std::cout << "Write login and password" << std::endl;
        inputStr = logInInput();
        break;
    }
    case SIGN_UP_USER: {
        std::cout << "Write login and password" << std::endl;
        inputStr = signUpInput();
        break;
    }
    case -1:
        break;
    default:
        std::cout << "Wrong command. Try again" << std::endl;
        break;
    }
    return inputStr;
}

void ConsoleView::PrintCommands() {
    std::cout << std::endl;
    std::cout << "Please choose command type:" << std::endl;
    std::cout << "- 0.Create Room" << std::endl
              << "- 1.Remove Room" << std::endl
              << "- 2.Add users" << std::endl
              << "- 3.Remove users" << std::endl
              << "- 4.Add link" << std::endl
              << "- 5.Remove link" << std::endl
              << "- 6.Make snapshot" << std::endl
              << "- 7.Log in" << std::endl
              << "- 8.Sign up" << std::endl
              << "- (-1).Exit" << std::endl;
}