#include "formRequest.hpp"

bool FormCreateRoomRequest::can_handle(int command) {
  return command == CREATE_ROOM;

}

std::unique_ptr<BaseHandler> FormCreateRoomRequest::spawn_handler(std::vector<std::string> &request_elements) {
  if (request_elements.size() < 2) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  RoomRequest request(request_elements[0], request_elements[1]);

  std::unique_ptr<Creator<RoomRequest>> creator = std::make_unique<CreateRoomHandlerCreator<RoomRequest>>();

  return creator->factory_method(request);
}

bool FormDeleteRoomRequest::can_handle(int command) {
  return command == DELETE_ROOM;

}

std::unique_ptr<BaseHandler> FormDeleteRoomRequest::spawn_handler(std::vector<std::string> &request_elements) {
  if (request_elements.size() < 2) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  RoomRequest request(request_elements[0], request_elements[1]);

  std::unique_ptr<Creator<RoomRequest>> creator = std::make_unique<DeleteRoomHandlerCreator<RoomRequest>>();

  return creator->factory_method(request);
};

bool FormAddLinkRequest::can_handle(int command) {
  return command == ADD_LINK;

}

std::unique_ptr<BaseHandler> FormAddLinkRequest::spawn_handler(std::vector<std::string> &request_elements) {
  if (request_elements.size() < 3) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  LinkRequest request(request_elements[0], request_elements[1], request_elements[2]);

  std::unique_ptr<Creator<LinkRequest>> creator = std::make_unique<AddLinkHandlerCreator<LinkRequest>>();

  return creator->factory_method(request);
}

bool FormDeleteLinkRequest::can_handle(int command) {
  return command == DELETE_LINK;
}

std::unique_ptr<BaseHandler> FormDeleteLinkRequest::spawn_handler(std::vector<std::string> &request_elements) {
  if (request_elements.size() < 3) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  LinkRequest request(request_elements[0], request_elements[1], request_elements[2]);

  std::unique_ptr<Creator<LinkRequest>> creator = std::make_unique<DeleteLinkHandlerCreator<LinkRequest>>();

  return creator->factory_method(request);
}

bool FormAddUserToRoomRequest::can_handle(int command) {
  return command == ADD_USERS;

}

std::unique_ptr<BaseHandler> FormAddUserToRoomRequest::spawn_handler(std::vector<std::string> &request_elements) {
  if (request_elements.size() < 3) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  std::vector<std::string> participants = request_split(request_elements[2]);

  UsersRoomRequest request(request_elements[0], request_elements[1], participants);

  std::unique_ptr<Creator<UsersRoomRequest>> creator = std::make_unique<AddUserToRoomHandlerCreator<UsersRoomRequest>>();

  return creator->factory_method(request);
}

bool FormDeleteUserFromRoomRequest::can_handle(int command) {
  return command == DELETE_USERS;

}

std::unique_ptr<BaseHandler> FormDeleteUserFromRoomRequest::spawn_handler(std::vector<std::string> &request_elements) {
  if (request_elements.size() < 3) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  std::vector<std::string> participants = request_split(request_elements[2]);

  UsersRoomRequest request(request_elements[0], request_elements[1], participants);

  std::unique_ptr<Creator<UsersRoomRequest>> creator = std::make_unique<DeleteUserFromRoomHandlerCreator<UsersRoomRequest>>();

  return creator->factory_method(request);
}

bool FormGetSnapshotRequest::can_handle(int command) {
  return command == MAKE_SNAPSHOT;
}

std::unique_ptr<BaseHandler> FormGetSnapshotRequest::spawn_handler(std::vector<std::string> &request_elements) {
  if (request_elements.size() < 3) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  SnapshotRequest request(request_elements[0], request_elements[1], request_elements[2]);

  std::unique_ptr<Creator<SnapshotRequest>> creator = std::make_unique<GetSnapshotHandlerCreator<SnapshotRequest>>();

  return creator->factory_method(request);
}