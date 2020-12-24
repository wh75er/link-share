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

  try {
    handler = parser->parse(data);
  }
  catch (const std::exception& e) {
    std::shared_ptr<Response>response = std::make_shared<Response>();
    response->error = e.what();
    sender.send(response);
    return;
  }

  // set model and response on handler

  handler->set_model(std::make_shared<Model<DbOps, Uuid>>(dbops));

  // execute handler
  handler->execute();

  std::shared_ptr<Response> response = handler->get_response();

  // use sender to send data back to client

  sender.send(response);
}
