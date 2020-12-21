#pragma once

#include <iostream>

template<class JsonParser>
TcpStringBodyParser<JsonParser>::TcpStringBodyParser() {
  registeredRequestFormers.push_back(std::make_unique<FormCreateRoomRequest<JsonParser>>());
  registeredRequestFormers.push_back(std::make_unique<FormDeleteRoomRequest<JsonParser>>());
  registeredRequestFormers.push_back(std::make_unique<FormAddLinkRequest<JsonParser>>());
  registeredRequestFormers.push_back(std::make_unique<FormDeleteLinkRequest<JsonParser>>());
  registeredRequestFormers.push_back(std::make_unique<FormAddUserToRoomRequest<JsonParser>>());
  registeredRequestFormers.push_back(std::make_unique<FormDeleteUserFromRoomRequest<JsonParser>>());
  registeredRequestFormers.push_back(std::make_unique<FormGetSnapshotRequest<JsonParser>>());
}

template<class JsonParser>
std::shared_ptr<BaseHandler> TcpStringBodyParser<JsonParser>::parse(std::string data) {
  if (data.empty()) {
    throw std::runtime_error("Input data is empty!");
  }

  std::shared_ptr<JsonParser> json = nullptr;
  try {
    json = std::make_unique<JsonParser>(data);
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

  std::shared_ptr<BaseHandler> handler = nullptr;

  for (auto &requestFormer : registeredRequestFormers) {
    if (requestFormer->can_handle(command)) {
      try {
        handler = requestFormer->spawn_handler(json);
      }
      catch (...) {
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
