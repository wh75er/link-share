#include "view.hpp"
#include "utils.h"
#include "inputUtils.hpp"
#include <iostream>

IView::~IView() {}


/* enum RequestCommand {
    CREATE_ROOM,
    DELETE_ROOM,
    ADD_USERS,
    DELETE_USERS,
    ADD_LINK,
    DELETE_LINK,
    MAKE_SNAPSHOT,
    LOG_IN_USER,
    SIGN_UP_USER,
    DOWNLOAD_SNAPSHOT,
    GET_USER_ROOM,
    GET_USER_LINKS,
    GET_LINK_SNAPSHOTS
}; */

enum RequestCommand {
    ADD_LINK,
    DELETE_LINK,
    MAKE_SNAPSHOT,
    LOG_IN_USER,
    SIGN_UP_USER,
    DOWNLOAD_SNAPSHOT,
    GET_USER_ROOM,
    GET_USER_LINKS,
    GET_LINK_SNAPSHOTS
};


std::string ConsoleView::GetRequest() {
    PrintCommands();

    std::string inputStr(""), appendStr(" ");
    int key = 0;
    std::cin >> key;
    getchar();
   /*  int a = 0;
    std::cin >> a; */
    switch (key) {
    /* case CREATE_ROOM: {
        std::cout << "Write name of room and is it private(true/false)" << std::endl;
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
        break; */
    case ADD_LINK: {
        std::cout << "Write name, url and description of link" << std::endl;
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
    case DOWNLOAD_SNAPSHOT: {
        std::cout << "Write uuid of snapshot and directory " << std::endl;
        inputStr = downloadSnapshotInput();
        break;
    }
    case GET_USER_ROOM: {
        //std::cout << "Write name of link and directory " << std::endl;
        inputStr = getUserRoomInput();
        break;
    }
    case GET_USER_LINKS: {
        inputStr = getUserLinksInput();
        break;
    }
    case GET_LINK_SNAPSHOTS: {
        std::cout << "Write name of link" << std::endl;
        inputStr = getLinkSnapshotsInput();
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

/* void ConsoleView::PrintCommands() {
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
              << "- 9.Download snapshot" << std::endl
              << "- 10.Get user room" << std::endl
              << "- 11.Get user links" << std::endl
              << "- 12.Get link snapshots" << std::endl
              << "- (-1).Exit" << std::endl;
} */


void ConsoleView::PrintCommands() {
    std::cout << std::endl;
    std::cout << "Please choose command type:" << std::endl;
    std::cout << "- 0.Add link" << std::endl
              << "- 1.Remove link" << std::endl
              << "- 2.Make snapshot" << std::endl
              << "- 3.Log in" << std::endl
              << "- 4.Sign up" << std::endl
              << "- 5.Download snapshot" << std::endl
              << "- 6.Create link storage" << std::endl
              << "- 7.Get user links" << std::endl
              << "- 8.Get link snapshots" << std::endl
              << "- (-1).Exit" << std::endl;
}