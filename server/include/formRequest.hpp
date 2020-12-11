#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include "requestCommands.hpp"
#include "request.hpp"
#include "utilities/split.hpp"
#include "handlers/baseHandler.hpp"
#include "handlers/handlerCreator.hpp"

class AbstractFormRequest {
public:
  ~AbstractFormRequest() {};

  virtual bool can_handle(int command) = 0;

  virtual std::shared_ptr<BaseHandler> spawn_handler(std::vector<std::string>& request_elements) = 0;
};

class FormCreateRoomRequest : public AbstractFormRequest {
public:
  FormCreateRoomRequest() {};
  ~FormCreateRoomRequest() {};

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::vector<std::string>& request_elements) override;
};

class FormDeleteRoomRequest : public AbstractFormRequest {
public:
  FormDeleteRoomRequest() {};
  ~FormDeleteRoomRequest() {};

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::vector<std::string>& request_elements) override;
};

class FormAddLinkRequest : public AbstractFormRequest {
public:
  FormAddLinkRequest() {};
  ~FormAddLinkRequest() {};

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::vector<std::string>& request_elements) override;
};

class FormDeleteLinkRequest : public AbstractFormRequest {
public:
  FormDeleteLinkRequest() {};
  ~FormDeleteLinkRequest() {};

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::vector<std::string>& request_elements) override;
};

class FormAddUserToRoomRequest : public AbstractFormRequest {
public:
  FormAddUserToRoomRequest() {};
  ~FormAddUserToRoomRequest() {};

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::vector<std::string>& request_elements) override;
};

class FormDeleteUserFromRoomRequest : public AbstractFormRequest {
public:
  FormDeleteUserFromRoomRequest() {};
  ~FormDeleteUserFromRoomRequest() {};

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::vector<std::string>& request_elements) override;
};

class FormGetSnapshotRequest : public AbstractFormRequest {
public:
  FormGetSnapshotRequest() {};
  ~FormGetSnapshotRequest() {};

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::vector<std::string>& request_elements) override;
};
