#include "errors.hpp"

int BaseError::get_code() const {
  return code;
}

const char* AddrInfoDefaultError::from() const {
  return gai_strerror(code);
}

const char* SocketDefaultError::from() const {
  return strerror(code);
}


const char* AddrInfoException::what() const noexcept {
  return error.from();
}

const char* SocketException::what() const noexcept {
  return error.from();
}

const char* ServerException::what() const noexcept {
  return error.from();
}
