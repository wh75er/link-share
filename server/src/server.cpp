#include "server.hpp"

TCPserver::TCPserver(std::string address, int port)
  : acceptor_(ioc_),
    address_(address), 
    port_(port)
{
  // Create non-blocking socket and bind it
}

void TCPserver::accept(std::shared_ptr<Connection> connection) {
  // Accept connection and create Connection object
}

void TCPserver::listen() {
  // listen for connections
  
  // If connection available, accept it(create Connection)
  
  // Run Connection

  // Continue to listen for other connections

  return;
}
