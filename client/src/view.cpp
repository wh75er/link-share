#include "view.hpp"
#include "utils.h"

#include <iostream>

IView::~IView() {}


std::string ConsoleView::GetRequest() {
    PrintCommands();

    std::string inputStr(""), appendStr(" ");
    int key = 0;
    std::cin >> key;
    switch (key) {
    case 1: {
        inputStr += "1,";
        std::cout << "Write name of room" << std::endl;
        std::cin >> appendStr;
        inputStr += "*Name*," + appendStr + ",";
        std::cout << "Write host of room" << std::endl;
        std::cin >> appendStr;
        inputStr += "*Host*," + appendStr + ",";
    }
        break;
    case 2: {
        inputStr += "2,";
        std::cout << "Write name of room" << std::endl;
        std::cin >> appendStr;
        inputStr += "*Name," + appendStr + ",";
        std::cout << "Write host of room" << std::endl;
        std::cin >> appendStr;
        inputStr += "*Host*," + appendStr + ",";
    }
        break;
    case 3: {
        inputStr += "3,";
        std::cout << "Write amount of users" << std::endl;
        size_t amount = 0;
        std::cin >> amount;
        inputStr += "*Users*,";
        std::cout << "Write users" << std::endl;
        while(amount > 0) {
            //std::getline(std::cin, appendStr);
            std::cin >> appendStr;
            inputStr += appendStr + ",";
            --amount;
           /* std::cout << amount<< std::endl; */
        }
    }
        break;
    case 4: {
        inputStr += "4,";
        std::cout << "Write amount of users" << std::endl;
        size_t amount = 0;
        std::cin >> amount;
        inputStr += "*Users*,";
        std::cout << "Write users" << std::endl;
        while(amount > 0) {
            std::cin >> appendStr;
            inputStr += appendStr + ",";
            --amount;
        }
    }
        break;
    case 5: {
        inputStr += "5,";
        std::cout << "Write name of link" << std::endl;
        std::cin >> appendStr;
        inputStr += "*Name*," + appendStr + ",";
        std::cout << "Write url of link" << std::endl;
        std::cin >> appendStr;
        inputStr += "*Url*," + appendStr + ",";
        break;
    }
    case 6: {
        inputStr += "6,";
        std::cout << "Write name of link" << std::endl;
        std::cin >> appendStr;
        inputStr += "*Name*," + appendStr + ",";
    }
        break;
    case 7: {
        inputStr += "7,";
        std::cout << "Write name of link" << std::endl;
        std::cin >> appendStr;
        inputStr += "*Name*," + appendStr + ",";
    }
        break;
    case 0:
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
    std::cout << "- 1.Create Room" << std::endl
              << "- 2.Remove Room" << std::endl
              << "- 3.Add users" << std::endl
              << "- 4.Remove users" << std::endl
              << "- 5.Add link" << std::endl
              << "- 6.Remove link" << std::endl
              << "- 7.Archive link" << std::endl
              << "- 0.Exit" << std::endl;
}