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

template<class Json, class Model>
class AbstractFormRequest {
public:
  virtual ~AbstractFormRequest() = default;

  virtual bool can_handle(int command) = 0;

  virtual std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) = 0;
};

template<class Json, class Model>
class FormCreateRoomRequest : public AbstractFormRequest<Json, Model> {
public:
  FormCreateRoomRequest() = default;
  ~FormCreateRoomRequest() override = default ;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json, class Model>
class FormDeleteRoomRequest : public AbstractFormRequest<Json, Model> {
public:
  FormDeleteRoomRequest() = default;
  ~FormDeleteRoomRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json, class Model>
class FormAddLinkRequest : public AbstractFormRequest<Json, Model> {
public:
  FormAddLinkRequest() = default;
  ~FormAddLinkRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json, class Model>
class FormDeleteLinkRequest : public AbstractFormRequest<Json, Model> {
public:
  FormDeleteLinkRequest() = default;
  ~FormDeleteLinkRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json, class Model>
class FormAddUserToRoomRequest : public AbstractFormRequest<Json, Model> {
public:
  FormAddUserToRoomRequest() = default;
  ~FormAddUserToRoomRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json, class Model>
class FormDeleteUserFromRoomRequest : public AbstractFormRequest<Json, Model> {
public:
  FormDeleteUserFromRoomRequest() = default;
  ~FormDeleteUserFromRoomRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json, class Model>
class FormCreateSnapshotRequest : public AbstractFormRequest<Json, Model> {
public:
  FormCreateSnapshotRequest() = default;
  ~FormCreateSnapshotRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json, class Model>
class FormLogInUserRequest : public AbstractFormRequest<Json, Model> {
public:
  FormLogInUserRequest() = default;
  ~FormLogInUserRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json, class Model>
class FormSignUpUserRequest : public AbstractFormRequest<Json, Model> {
public:
  FormSignUpUserRequest() = default;
  ~FormSignUpUserRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

template<class Json, class Model>
class FormGetSnapshotRequest : public AbstractFormRequest<Json, Model> {
public:
  FormGetSnapshotRequest() = default;
  ~FormGetSnapshotRequest() override = default;

  bool can_handle(int command) override;

  std::shared_ptr<BaseHandler<Model>> spawn_handler(std::shared_ptr<Json> request_elements) override;
};

#include "formRequest.tpp"