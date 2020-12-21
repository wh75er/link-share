#pragma once

#include <errno.h>
#include <stdexcept>
#include <string>
#include <string.h>
#include <netdb.h>
#include <memory>

enum DatabaseErrorCode {
  CONNECTION_FAILED_ERR,
};

enum ParseErrorCode {
  PARSE_FAILURE,
  VALUE_NOT_FOUND,
  UNKNOWN_COMMAND,
};

class BaseError {
  public:
    explicit BaseError(const int &_code):
      code(_code)
      {}

    virtual const char* from() const = 0;
    virtual int get_code() const;

  protected:
    int code;
};

class ParseError: public BaseError {
public:
  explicit ParseError(const int& _code):
    BaseError(_code)
  {}

  const char* from() const override;
};

class DatabaseError : public BaseError {
public:
  explicit DatabaseError(const int &_code):
    BaseError(_code)
  {}

  const char* from() const override;
};

class AddrInfoDefaultError : public BaseError {
  public:
    explicit AddrInfoDefaultError(const int &_code):
      BaseError(_code)
      {}

    const char* from() const override;
};

class SocketDefaultError : public BaseError {
  public:
    explicit SocketDefaultError(const int &_code):
      BaseError(_code)
      {}

    const char* from() const override;
};

class BaseException : public std::exception {
  public: 
    explicit BaseException(std::shared_ptr<BaseError> _e):
      error(std::move(_e)),
      msg("")
      {}

    explicit BaseException(std::shared_ptr<BaseError> _e, const std::string& _msg):
      error(std::move(_e)),
      msg(_msg)
      {}

    virtual ~BaseException() noexcept {}

    virtual const char* what() const noexcept = 0;

    std::shared_ptr<BaseError> error;
    std::string msg;
};

class AddrInfoException : public BaseException {
  public: 
    explicit AddrInfoException(std::shared_ptr<BaseError> _e):
      BaseException(std::move(_e))
      {}

    explicit AddrInfoException(std::shared_ptr<BaseError> _e, const std::string& _msg):
      BaseException(std::move(_e), _msg)
      {}

    virtual ~AddrInfoException() noexcept {}

    const char* what() const noexcept override;
};

class SocketException : public BaseException {
  public: 
    explicit SocketException(std::shared_ptr<BaseError> _e):
      BaseException(std::move(_e))
      {}

    explicit SocketException(std::shared_ptr<BaseError> _e, const std::string& _msg):
      BaseException(std::move(_e), _msg)
      {}

    virtual ~SocketException() noexcept {}

    const char* what() const noexcept override;
};

class ServerException : public BaseException {
  public: 
    explicit ServerException(std::shared_ptr<BaseError> _e):
      BaseException(std::move(_e))
      {}

    explicit ServerException(std::shared_ptr<BaseError> _e, const std::string& _msg):
      BaseException(std::move(_e), _msg)
      {}

    virtual ~ServerException() noexcept {}

    const char* what() const noexcept override;
};

class ParserException : public BaseException {
public:
  explicit ParserException(std::shared_ptr<BaseError> _e):
    BaseException(std::move(_e))
  {}

  explicit ParserException(std::shared_ptr<BaseError> _e, const std::string& _msg):
    BaseException(std::move(_e), _msg)
  {}

  virtual ~ParserException() noexcept {}

  const char* what() const noexcept override;
};
