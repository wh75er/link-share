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
#include "errors.hpp"

template<class Json>
class AbstractFormRequest {
public:
  virtual ~AbstractFormRequest() = default;

  virtual bool can_handle(int command) = 0;

  virtual std::shared_ptr<BaseHandler> spawn_handler(std::shared_ptr<Json> request_elements) = 0;
};

template<class Json>
class FormCreateRoomRequest : public AbstractFormRequest<Json> {
public:
  FormCreateRoomRequest() = default;
  ~FormCreateRoomRequest() override = default ;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json>
class FormDeleteRoomRequest : public AbstractFormRequest<Json> {
public:
  FormDeleteRoomRequest() = default;
  ~FormDeleteRoomRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json>
class FormAddLinkRequest : public AbstractFormRequest<Json> {
public:
  FormAddLinkRequest() = default;
  ~FormAddLinkRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json>
class FormDeleteLinkRequest : public AbstractFormRequest<Json> {
public:
  FormDeleteLinkRequest() = default;
  ~FormDeleteLinkRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json>
class FormAddUserToRoomRequest : public AbstractFormRequest<Json> {
public:
  FormAddUserToRoomRequest() = default;
  ~FormAddUserToRoomRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json>
class FormDeleteUserFromRoomRequest : public AbstractFormRequest<Json> {
public:
  FormDeleteUserFromRoomRequest() = default;
  ~FormDeleteUserFromRoomRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json>
class FormGetSnapshotRequest : public AbstractFormRequest<Json> {
public:
  FormGetSnapshotRequest() = default;
  ~FormGetSnapshotRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

#include "formRequest.tpp"