#pragma once

template<class Json, class Model>
bool FormCreateRoomRequest<Json, Model>::can_handle(int command) {
  return command == CREATE_ROOM;

}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormCreateRoomRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {

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


  std::shared_ptr<Creator<RoomRequest, Model>> creator = std::make_unique<CreateRoomHandlerCreator<RoomRequest, Model>>();

  return creator->factory_method(request);
}

template<class Json, class Model>
bool FormDeleteRoomRequest<Json, Model>::can_handle(int command) {
  return command == DELETE_ROOM;

}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormDeleteRoomRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {
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

  std::shared_ptr<Creator<RoomRequest, Model>> creator = std::make_unique<DeleteRoomHandlerCreator<RoomRequest, Model>>();

  return creator->factory_method(request);
}

template<class Json, class Model>
bool FormAddLinkRequest<Json, Model>::can_handle(int command) {
  return command == ADD_LINK;
}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormAddLinkRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {
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

  std::shared_ptr<Creator<LinkRequest, Model>> creator = std::make_unique<AddLinkHandlerCreator<LinkRequest, Model>>();

  return creator->factory_method(request);
}

template<class Json, class Model>
bool FormDeleteLinkRequest<Json, Model>::can_handle(int command) {
  return command == DELETE_LINK;
}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormDeleteLinkRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {
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

  std::shared_ptr<Creator<LinkRequest, Model>> creator = std::make_unique<DeleteLinkHandlerCreator<LinkRequest, Model>>();

  return creator->factory_method(request);
}

template<class Json, class Model>
bool FormAddUserToRoomRequest<Json, Model>::can_handle(int command) {
  return command == ADD_USERS;

}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormAddUserToRoomRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {
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

  std::shared_ptr<Creator<UsersRoomRequest, Model>> creator = std::make_unique<AddUserToRoomHandlerCreator<UsersRoomRequest, Model>>();

  return creator->factory_method(request);
}

template<class Json, class Model>
bool FormDeleteUserFromRoomRequest<Json, Model>::can_handle(int command) {
  return command == DELETE_USERS;

}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormDeleteUserFromRoomRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {
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

  std::shared_ptr<Creator<UsersRoomRequest, Model>> creator = std::make_unique<DeleteUserFromRoomHandlerCreator<UsersRoomRequest, Model>>();

  return creator->factory_method(request);
}

template<class Json, class Model>
bool FormCreateSnapshotRequest<Json, Model>::can_handle(int command) {
  return command == MAKE_SNAPSHOT;
}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormCreateSnapshotRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {
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

  std::shared_ptr<Creator<SnapshotRequest, Model>> creator = std::make_unique<CreateSnapshotHandlerCreator<SnapshotRequest, Model>>();

  return creator->factory_method(request);
}

template<class Json, class Model>
bool FormLogInUserRequest<Json, Model>::can_handle(int command) {
  return command == LOG_IN_USER;
}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormLogInUserRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {
  std::string login;
  if (!request_elements->get_value("login", login)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "login value is not presented in JSON!");
  }

  std::string password;
  if (!request_elements->get_value("password", password)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "token value is not presented in JSON!");
  }

  UserRequest request(login, password);

  std::shared_ptr<Creator<UserRequest, Model>> creator = std::make_unique<GetLogInUserHandlerCreator<UserRequest, Model>>();

  return creator->factory_method(request);
}

template<class Json, class Model>
bool FormSignUpUserRequest<Json, Model>::can_handle(int command) {
  return command == SIGN_UP_USER;
}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormSignUpUserRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {
  std::cout << "Getting inside the handler!" << std::endl;

  std::string login;
  if (!request_elements->get_value("login", login)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "login value is not presented in JSON!");
  }

  std::cout << "Login is : " << login << std::endl;

  std::string password;
  if (!request_elements->get_value("password", password)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "token value is not presented in JSON!");
  }

  std::cout << "Password is : " << password << std::endl;

  std::cout << "Forming request" << std::endl;

  UserRequest request(login, password);

  std::cout << "Request is formed!" << std::endl;

  std::shared_ptr<Creator<UserRequest, Model>> creator = std::make_unique<GetSignUpUserHandlerCreator<UserRequest, Model>>();

  return creator->factory_method(request);
}

template<class Json, class Model>
bool FormGetSnapshotRequest<Json, Model>::can_handle(int command) {
  return command == GET_SNAPSHOT;
}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormGetSnapshotRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {
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

  std::shared_ptr<Creator<SnapshotRequest, Model>> creator = std::make_unique<GetSnapshotHandlerCreator<SnapshotRequest, Model>>();

  return creator->factory_method(request);
}

template<class Json, class Model>
bool FormGetUserRoomRequest<Json, Model>::can_handle(int command) {
  return command == GET_USER_ROOM;
}

template<class Json, class Model>
std::shared_ptr<BaseHandler<Model>> FormGetUserRoomRequest<Json, Model>::spawn_handler(std::shared_ptr<Json> request_elements) {
  std::string login;
  if (!request_elements->get_value("login", login)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "login value is not presented in JSON!");
  }

  std::string token;
  if (!request_elements->get_value("token", token)) {
    throw ParserException(std::make_shared<ParseError>(ParseErrorCode::VALUE_NOT_FOUND), "token value is not presented in JSON!");
  }

  BaseRequest request(login, token);

  std::shared_ptr<Creator<BaseRequest, Model>> creator = std::make_unique<GetUserRoomHandlerCreator<BaseRequest, Model>>();

  return creator->factory_method(request);
}
