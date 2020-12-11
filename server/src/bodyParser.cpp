#include "bodyParser.hpp"

TcpStringBodyParser::TcpStringBodyParser() {
  registeredRequestFormers.push_back(std::make_unique<FormCreateRoomRequest>());
  registeredRequestFormers.push_back(std::make_unique<FormDeleteRoomRequest>());
  registeredRequestFormers.push_back(std::make_unique<FormAddLinkRequest>());
  registeredRequestFormers.push_back(std::make_unique<FormDeleteLinkRequest>());
  registeredRequestFormers.push_back(std::make_unique<FormAddUserToRoomRequest>());
  registeredRequestFormers.push_back(std::make_unique<FormDeleteUserFromRoomRequest>());
  registeredRequestFormers.push_back(std::make_unique<FormGetSnapshotRequest>());
}

std::shared_ptr<BaseHandler> TcpStringBodyParser::parse(std::string data) {
  std::vector<std::string> input_elements = request_split(data);

  if (input_elements.empty()) {
    throw std::runtime_error("Parsed vector should not be empty!");
  }

  int command = std::stoi(input_elements[0]);
  input_elements.erase(input_elements.begin());

  std::shared_ptr<BaseHandler> handler = nullptr;

  for (auto &requestFormer : registeredRequestFormers) {
    if (requestFormer->can_handle(command)) {
      handler = requestFormer->spawn_handler(input_elements);
      break;
    }
  }

  if (!handler) {
    throw std::runtime_error("Presented command is not valid!");
  }

  return handler;
}
