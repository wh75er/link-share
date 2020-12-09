#include "server.hpp"
#include "errors.hpp"
#include "socket.hpp"
#include <string>
#include <iostream>

int main() {
  std::string address = "127.0.0.1";
  std::string port = "13201";

  try {
    TCPserver server = TCPserver(address, port);

    std::cout << "Set to listen" << std::endl;

    server.listen();

    std::cout << "Server starting on " << address << ":" << port << std::endl;

    server.accept();
  }
  catch (const BaseException& except){
    std::cout << except.what() << std::endl;
    std::cout << except.msg << std::endl;
  }

}
