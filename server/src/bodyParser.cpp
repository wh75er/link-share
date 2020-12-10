#include "bodyParser.hpp"

std::tuple<int, std::shared_ptr<BaseRequest>> TcpStringBodyParser::parse(std::string data) {
  std::vector<std::string> input_elements = request_split(data);

  if (input_elements.empty()) {
    throw std::runtime_error("Parsed vector should not be empty!");
  }

  int command = std::stoi(input_elements[0]);
  input_elements.erase(input_elements.begin());

  if (command == CREATE_ROOM || command == DELETE_ROOM) {
      return {command, form_room_request(input_elements)};
  } else if (command == ADD_USERS || command == DELETE_USERS) {
    return {command, form_users_room_request(input_elements)};
  } else if (command == ADD_LINK || command == DELETE_LINK) {
    return {command, form_link_request(input_elements)};
  } else if (command == MAKE_SNAPSHOT) {
    return {command, form_snapshot_request(input_elements)};
  } else {
    throw std::runtime_error("Presented command is not valid!");
  }
}

std::shared_ptr<RoomRequest> TcpStringBodyParser::form_room_request(std::vector<std::string>& request_elements) {
  if (request_elements.size() < 2) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  return std::make_shared<RoomRequest>(request_elements[0], request_elements[1]);
}

std::shared_ptr<UsersRoomRequest> TcpStringBodyParser::form_users_room_request(std::vector<std::string>& request_elements) {
  if (request_elements.size() < 3) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  std::vector<std::string> participants = request_split(request_elements[2]);

  return std::make_shared<UsersRoomRequest>(request_elements[0], request_elements[1], participants);
}

std::shared_ptr<LinkRequest> TcpStringBodyParser::form_link_request(std::vector<std::string>& request_elements) {
  if (request_elements.size() < 3) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  return std::make_shared<LinkRequest>(request_elements[0], request_elements[1], request_elements[2]);
}

std::shared_ptr<SnapshotRequest> TcpStringBodyParser::form_snapshot_request(std::vector<std::string>& request_elements) {
  if (request_elements.size() < 3) {
    throw std::runtime_error("Invalid amount of requested args!");
  }

  return std::make_shared<SnapshotRequest>(request_elements[0], request_elements[1], request_elements[2]);
}


std::vector<std::string> TcpStringBodyParser::request_split(std::string& data) {
  std::vector<std::string> elements;
  
  std::string element = "";

  bool special_block = false;

  for(auto it = data.begin(); it != data.end(); it++) {
    if (*it == '{' || *it == '}' || *it == '[' || *it == ']') {
      if (*it == '[' || *it == '{') {
        special_block = true;
      } else {
        special_block = false;
      }
    }

    if (*it == ',' && !special_block) {
      elements.push_back(element);
      element = "";
    } else {
      element += *it;
    }
  }

  return elements;
}
