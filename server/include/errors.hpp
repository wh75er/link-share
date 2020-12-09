#pragma once

#include <errno.h>
#include <stdexcept>
#include <string>
#include <string.h>
#include <netdb.h>
#include <memory>

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
      error(_e),
      msg("")
      {}

    explicit BaseException(std::shared_ptr<BaseError> _e, const std::string& _msg):
      error(_e),
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
      BaseException(_e)
      {}

    explicit AddrInfoException(std::shared_ptr<BaseError> _e, const std::string& _msg):
      BaseException(_e, _msg)
      {}

    virtual ~AddrInfoException() noexcept {}

    const char* what() const noexcept override;
};

class SocketException : public BaseException {
  public: 
    explicit SocketException(std::shared_ptr<BaseError> _e):
      BaseException(_e)
      {}

    explicit SocketException(std::shared_ptr<BaseError> _e, const std::string& _msg):
      BaseException(_e, _msg)
      {}

    virtual ~SocketException() noexcept {}

    const char* what() const noexcept override;
};

class ServerException : public BaseException{
  public: 
    explicit ServerException(std::shared_ptr<BaseError> _e):
      BaseException(_e)
      {}

    explicit ServerException(std::shared_ptr<BaseError> _e, const std::string& _msg):
      BaseException(_e, _msg)
      {}

    virtual ~ServerException() noexcept {}

    const char* what() const noexcept override;
};
