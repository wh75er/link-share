#include "server.hpp"

TCPserver::TCPserver(std::string address, std::string port):
  address_(address), 
  port_(port)
{
  // Create non-blocking socket and bind it
  socket_ = TcpSocket::Builder()
    .address(address)
    .port(port)
    .non_blocking()
    .build();

  try {
    socket_.create();
  } 
  catch (const BaseException& except) {
    throw ServerException(except.error);
  }

  try {
    socket_.bind_();
  }
  catch (const BaseException& except) {
    throw ServerException(except.error);
  }
}

void TCPserver::accept(std::shared_ptr<Connection> connection) {
  // Accept connection and create Connection object
}

void TCPserver::listen() {
  // listen for connections
  try {
    socket_.listen_();
  }
  catch (const BaseException& except) {
    throw ServerException(except.error);
  }
  
  // If connection available, accept it(create Connection)
  
  // Run Connection

  // Continue to listen for other connections
}
