#pragma once

template<class Json>
bool FormCreateRoomRequest<Json>::can_handle(int command) {
  return command == CREATE_ROOM;

}

template<class Json>
std::shared_ptr<BaseHandler> FormCreateRoomRequest<Json>::spawn_handler(std::shared_ptr<Json> request_elements) {

  std::string login;
  if (!request_elements->get_value("login", login)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "login value is not presented in JSON!");
  }

  std::string token;
  if (!request_elements->get_value("token", token)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "token value is not presented in JSON!");
  }

  std::string name;
  if (!request_elements->get_value("name", name)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "name value is not presented in JSON!");
  }

  bool private_ = false;
  if (!request_elements->get_value("private", private_)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "private value is not presented in JSON!");
  }

  RoomRequest request = RoomRequest::Builder()
          .login(login)
          .token(token)
          .name(name)
          .is_private(private_)
          .build();


  std::shared_ptr<Creator<RoomRequest>> creator = std::make_unique<CreateRoomHandlerCreator<RoomRequest>>();

  return creator->factory_method(request);
}

template<class Json>
bool FormDeleteRoomRequest<Json>::can_handle(int command) {
  return command == DELETE_ROOM;

}

template<class Json>
std::shared_ptr<BaseHandler> FormDeleteRoomRequest<Json>::spawn_handler(std::shared_ptr<Json> request_elements) {
  std::string login;
  if (!request_elements->get_value("login", login)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "login value is not presented in JSON!");
  }

  std::string token;
  if (!request_elements->get_value("token", token)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "token value is not presented in JSON!");
  }

  std::string uuid;
  if (!request_elements->get_value("uuid", uuid)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "uuid value is not presented in JSON!");
  }

  RoomRequest request = RoomRequest::Builder()
          .login(login)
          .token(token)
          .uuid(uuid)
          .build();

  std::shared_ptr<Creator<RoomRequest>> creator = std::make_unique<DeleteRoomHandlerCreator<RoomRequest>>();

  return creator->factory_method(request);
}

template<class Json>
bool FormAddLinkRequest<Json>::can_handle(int command) {
  return command == ADD_LINK;
}

template<class Json>
std::shared_ptr<BaseHandler> FormAddLinkRequest<Json>::spawn_handler(std::shared_ptr<Json> request_elements) {
  std::string login;
  if (!request_elements->get_value("login", login)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "login value is not presented in JSON!");
  }

  std::string token;
  if (!request_elements->get_value("token", token)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "token value is not presented in JSON!");
  }

  std::string uuid;
  if (!request_elements->get_value("uuid", uuid)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "uuid value is not presented in JSON!");
  }

  std::string url;
  if (!request_elements->get_value("url", url)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "url value is not presented in JSON!");
  }

  std::string name;
  if (!request_elements->get_value("name", name)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "name value is not presented in JSON!");
  }

  std::string description;
  if (!request_elements->get_value("description", description)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "description value is not presented in JSON!");
  }

  LinkRequest request = LinkRequest::Builder()
          .login(login)
          .token(token)
          .uuid(uuid)
          .url(url)
          .name(name)
          .description(description)
          .build();

  std::shared_ptr<Creator<LinkRequest>> creator = std::make_unique<AddLinkHandlerCreator<LinkRequest>>();

  return creator->factory_method(request);
}

template<class Json>
bool FormDeleteLinkRequest<Json>::can_handle(int command) {
  return command == DELETE_LINK;
}

template<class Json>
std::shared_ptr<BaseHandler> FormDeleteLinkRequest<Json>::spawn_handler(std::shared_ptr<Json> request_elements) {
  std::string login;
  if (!request_elements->get_value("login", login)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "login value is not presented in JSON!");
  }

  std::string token;
  if (!request_elements->get_value("token", token)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "token value is not presented in JSON!");
  }

  std::string uuid;
  if (!request_elements->get_value("uuid", uuid)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "uuid value is not presented in JSON!");
  }

  LinkRequest request = LinkRequest::Builder()
          .login(login)
          .token(token)
          .uuid(uuid)
          .build();

  std::shared_ptr<Creator<LinkRequest>> creator = std::make_unique<DeleteLinkHandlerCreator<LinkRequest>>();

  return creator->factory_method(request);
}

template<class Json>
bool FormAddUserToRoomRequest<Json>::can_handle(int command) {
  return command == ADD_USERS;

}

template<class Json>
std::shared_ptr<BaseHandler> FormAddUserToRoomRequest<Json>::spawn_handler(std::shared_ptr<Json> request_elements) {
  std::string login;
  if (!request_elements->get_value("login", login)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "login value is not presented in JSON!");
  }

  std::string token;
  if (!request_elements->get_value("token", token)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "token value is not presented in JSON!");
  }

  std::string uuid;
  if (!request_elements->get_value("uuid", uuid)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "uuid value is not presented in JSON!");
  }

  std::vector<std::string> users;
  if (!request_elements->get_value("users", users)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "users value is not presented in JSON!");
  }

  UsersRoomRequest request(login, token, uuid, users);

  std::shared_ptr<Creator<UsersRoomRequest>> creator = std::make_unique<AddUserToRoomHandlerCreator<UsersRoomRequest>>();

  return creator->factory_method(request);
}

template<class Json>
bool FormDeleteUserFromRoomRequest<Json>::can_handle(int command) {
  return command == DELETE_USERS;

}

template<class Json>
std::shared_ptr<BaseHandler> FormDeleteUserFromRoomRequest<Json>::spawn_handler(std::shared_ptr<Json> request_elements) {
  std::string login;
  if (!request_elements->get_value("login", login)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "login value is not presented in JSON!");
  }

  std::string token;
  if (!request_elements->get_value("token", token)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "token value is not presented in JSON!");
  }

  std::string uuid;
  if (!request_elements->get_value("uuid", uuid)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "uuid value is not presented in JSON!");
  }

  std::vector<std::string> users;
  if (!request_elements->get_value("users", users)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "users value is not presented in JSON!");
  }

  UsersRoomRequest request(login, token, uuid, users);

  std::shared_ptr<Creator<UsersRoomRequest>> creator = std::make_unique<DeleteUserFromRoomHandlerCreator<UsersRoomRequest>>();

  return creator->factory_method(request);
}

template<class Json>
bool FormGetSnapshotRequest<Json>::can_handle(int command) {
  return command == MAKE_SNAPSHOT;
}

template<class Json>
std::shared_ptr<BaseHandler> FormGetSnapshotRequest<Json>::spawn_handler(std::shared_ptr<Json> request_elements) {
  std::string login;
  if (!request_elements->get_value("login", login)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "login value is not presented in JSON!");
  }

  std::string token;
  if (!request_elements->get_value("token", token)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "token value is not presented in JSON!");
  }

  std::string uuid;
  if (!request_elements->get_value("uuid", uuid)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "uuid value is not presented in JSON!");
  }
  SnapshotRequest request(login, token, uuid);

  std::shared_ptr<Creator<SnapshotRequest>> creator = std::make_unique<GetSnapshotHandlerCreator<SnapshotRequest>>();

  return creator->factory_method(request);
}
