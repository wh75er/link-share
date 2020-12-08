#pragma once

#include <errno.h>
#include <stdexcept>
#include <string>
#include <string.h>
#include <netdb.h>

class BaseError {
  public:
    explicit BaseError(const int &_code):
      code(_code)
      {}

    virtual const char* from() const;
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
    explicit BaseException(const BaseError _e):
      error(_e)
      {}

    virtual ~BaseException() noexcept {}

    virtual const char* what() const noexcept;

    BaseError error;
};

class AddrInfoException : public BaseException {
  public: 
    explicit AddrInfoException(const BaseError _e):
      BaseException(_e)
      {}

    virtual ~AddrInfoException() noexcept {}

    const char* what() const noexcept override;
};

class SocketException : public BaseException {
  public: 
    explicit SocketException(const BaseError _e):
      BaseException(_e)
      {}

    virtual ~SocketException() noexcept {}

    const char* what() const noexcept override;
};

class ServerException : public BaseException{
  public: 
    explicit ServerException(const BaseError _e):
      BaseException(_e)
      {}

    virtual ~ServerException() noexcept {}

    const char* what() const noexcept override;
};
