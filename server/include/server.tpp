#pragma once

#include <iostream>

#define TRY_ACCEPT_AGAIN -1
#define TIMEOUT_MILLS 100

template<class DbOps, class Uuid, class JsonParser>
TCPserver<DbOps, Uuid, JsonParser>::TCPserver(std::string address, std::string port):
        address_(address),
        port_(port),
        running_(false)
{
//  std::cout << "Came Address is : " << address << std::endl;
//  std::cout << "Came Port is : " << port << std::endl;
//
//  std::cout << "Address is : " << address_ << std::endl;
//  std::cout << "Port is : " << port_ << std::endl;

  try {
    dbops = std::make_shared<DbOps>();
  }
  catch (...) {
    throw ServerException(
      std::make_shared<DatabaseError>(DatabaseErrorCode::CONNECTION_FAILED_ERR),
     "Failed to establish connection with database!"
    );
  }

  workers_count = std::thread::hardware_concurrency();

#ifdef DEBUG
  std::cout << "Worker count is : " << workers_count << std::endl;
#endif

  socket_ = std::make_shared<TcpSocket>(TcpSocket::Builder()
                                                .address(address)
                                                .port(port)
                                                .non_blocking()
                                                .build()
  );

  try {
    socket_->create();
  }
  catch (const BaseException& except) {
    throw ServerException(except.error, "Failed to create socket!");
  }

  try {
    socket_->bind_();
  }
  catch (const BaseException& except) {
    throw ServerException(except.error, "Failed to bind socket!");
  }
}

template<class DbOps, class Uuid, class JsonParser>
TCPserver<DbOps, Uuid, JsonParser>::~TCPserver() {
  socket_->close_();

  for (auto i = 0; i < futures.size(); i++) {
    futures[i].wait();
  }
}

template<class DbOps, class Uuid, class JsonParser>
void TCPserver<DbOps, Uuid, JsonParser>::accept() {
  running_ = true;

  while (running_) {
    // If connection available, accept it(create Connection)
    int connection_sd = TRY_ACCEPT_AGAIN;
    try {
      connection_sd = socket_->accept_();
    }
    catch (const BaseException& except) {
      throw ServerException(except.error, "Failed to accept socket connection!");
    }

    if (connection_sd == TRY_ACCEPT_AGAIN) {
#ifdef DEBUG
      std::cout << "There's no connections!" << std::endl;
#endif
      continue;
    }

#ifdef DEBUG
    std::cout << "Got a connection!(with socket )" << connection_sd << std::endl;
#endif

    TcpSocket connection_socket = TcpSocket::Builder()
            .socket(connection_sd)
            .build();

    // Accept connection and create Connection object
    if (futures.size() < workers_count) {
#ifdef DEBUG
      std::cout << "Futures size is " << futures.size() << std::endl;
#endif
      futures.push_back(std::async(std::launch::async, [connection_socket, this]() {std::make_shared<Connection<DbOps, Uuid, JsonParser>>(std::make_shared<TcpSocket>(connection_socket))->start(dbops);}));
    } else {
#ifdef DEBUG
      std::cout << "Futures size is full(" << futures.size() << ")" << std::endl;
#endif
      bool slot_found = false;

      while (!slot_found) {
#ifdef DEBUG
        std::cout << "Trying to finished future!" << std::endl;
#endif

        std::chrono::milliseconds time (TIMEOUT_MILLS);

        for (auto i = 0; i < futures.size() && !slot_found; i++) {
          if (futures[i].wait_for(time) == std::future_status::ready) {
#ifdef DEBUG
            std::cout << "Found finished future!" << std::endl;
            std::cout << "Occupying feature # " << i << std::endl;
#endif

            futures[i] = std::async(std::launch::async, [connection_socket, this]() {std::make_shared<Connection<DbOps, Uuid, JsonParser>>(std::make_shared<TcpSocket>(connection_socket))->start(dbops);});

            slot_found = true;
          }
        }
      }
    }

    // Continue to listen for other connections
  }
}

template<class DbOps, class Uuid, class JsonParser>
void TCPserver<DbOps, Uuid, JsonParser>::listen() {
  // listen for connections
  try {
    socket_->listen_();
  }
  catch (const BaseException& except) {
    throw ServerException(except.error, "Failed to set socket to listening!");
  }
#ifdef DEBUG
  std::cout << "Socket is listening!" << std::endl;
#endif
}

template<class DbOps, class Uuid, class JsonParser>
bool TCPserver<DbOps, Uuid, JsonParser>::is_running() {
  return running_;
}

template<class DbOps, class Uuid, class JsonParser>
void TCPserver<DbOps, Uuid, JsonParser>::stop_listen(int _) {
  running_ = false;
}
