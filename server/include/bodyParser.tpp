#pragma once

#include <iostream>

template<class Model, class JsonParser>
TcpStringBodyParser<Model, JsonParser>::TcpStringBodyParser() {
  registeredRequestFormers.push_back(std::make_unique<FormCreateRoomRequest<JsonParser, Model>>());
  registeredRequestFormers.push_back(std::make_unique<FormDeleteRoomRequest<JsonParser, Model>>());
  registeredRequestFormers.push_back(std::make_unique<FormAddLinkRequest<JsonParser, Model>>());
  registeredRequestFormers.push_back(std::make_unique<FormDeleteLinkRequest<JsonParser, Model>>());
  registeredRequestFormers.push_back(std::make_unique<FormAddUserToRoomRequest<JsonParser, Model>>());
  registeredRequestFormers.push_back(std::make_unique<FormDeleteUserFromRoomRequest<JsonParser, Model>>());
  registeredRequestFormers.push_back(std::make_unique<FormGetSnapshotRequest<JsonParser, Model>>());
  registeredRequestFormers.push_back(std::make_unique<FormLogInUserRequest<JsonParser, Model>>());
  registeredRequestFormers.push_back(std::make_unique<FormSignUpUserRequest<JsonParser, Model>>());
}

template<class Model, class JsonParser>
std::shared_ptr<BaseHandler<Model>> TcpStringBodyParser<Model, JsonParser>::parse(std::string data) {
  if (data.empty()) {
    throw std::runtime_error("Input data is empty!");
  }

  std::shared_ptr<JsonParser> json = nullptr;
  try {
    json = std::make_shared<JsonParser>(data);
  }
  catch (...) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::PARSE_FAILURE), "Failed to parse JSON!");
  }

  int command = -1;
  if (!json->get_value("command", command)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "Command value is not presented in JSON!");
  };

#ifdef DEBUG
  std::cout << "Is command found? : " << true << ", Command number is : " << command << std::endl;
#endif

  std::shared_ptr<BaseHandler<Model>> handler = nullptr;

  for (auto &requestFormer : registeredRequestFormers) {
    if (requestFormer->can_handle(command)) {
      try {
        handler = requestFormer->spawn_handler(json);
      }
      catch (std::exception& e) {
        std::cout << "Problem is : " << e.what() << std::endl;
        throw;
      }
      break;
    }
  }

  if (!handler) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::UNKNOWN_COMMAND), "Command is not valid!");
  }

  return handler;
}
