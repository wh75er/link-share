#pragma once

#include <chrono>
#include <future>
#include <functional>
#include <fcntl.h>
#include <errno.h>
#include <memory>
#include <string>

#include "connection.hpp"
#include "socket.hpp"

void exit_handler(int s);

class TCPserver {
public:
  explicit TCPserver(std::string address, std::string port);
  ~TCPserver();

  void accept();
  void listen();
  bool is_running();

private:
  void stop_listen(int _);

  std::shared_ptr<BaseTcpSocket> socket_;
  std::string address_ = "";
  std::string port_ = "";
  bool running_;
  size_t workers_count;
  std::vector<std::future<void>> futures;
};
