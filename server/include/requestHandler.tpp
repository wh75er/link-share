#pragma once

#include <unistd.h>

template<class DbOps, class Connection, class Uuid, class JsonParser>
RequestHandler<DbOps, Connection, Uuid, JsonParser>::RequestHandler(std::shared_ptr<Connection> connection, std::shared_ptr<DbOps> dbops_)
        : sender(std::move(connection)),
          dbops(dbops_)
{
#ifdef DEBUG
  std::cout <<  "RequestHandler constructor" << std::endl;
  unsigned int microseconds = 3 * 1e+6;
  usleep(microseconds);
#endif
}

template<class DbOps, class Connection, class Uuid, class JsonParser>
void RequestHandler<DbOps, Connection, Uuid, JsonParser>::handle(std::string data) {
#ifdef DEBUG
  std::cout << "Data inside of request handler is: " << data << std::endl;
#endif

  // Create parser & parse data
  parser = std::make_unique<TcpStringBodyParser<Model<DbOps, Uuid>, JsonParser>>();

  handler = parser->parse(data);

  handler->set_model(std::make_shared<Model<DbOps, Uuid>>(dbops));

  // set model and response on handler

  // execute handler

  // use sender to send data back to client

  sender.send(data);
}
