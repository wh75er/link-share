#pragma once

#include <iostream>

#include <string>
#include <memory>

#include "model.hpp"
#include "bodyParser.hpp"
#include "sender.hpp"
#include "handlers/baseHandler.hpp"

template<class DbOps, class Connection, class Uuid, class JsonParser>
class RequestHandler {
public:
  explicit RequestHandler(std::shared_ptr<Connection> connection, std::shared_ptr<DbOps> dbops_);
  ~RequestHandler() {
#ifdef DEBUG
    std::cout << "RequestHandler destructor" << std::endl;
#endif
  };

  void handle(std::string data);

private:
  std::unique_ptr<AbstractBodyParser<Model<DbOps, Uuid>>> parser = nullptr;
  std::shared_ptr<BaseHandler<Model<DbOps, Uuid>>> handler = nullptr;
  std::shared_ptr<DbOps> dbops;
  Sender<Connection> sender;
};

#include "requestHandler.tpp"