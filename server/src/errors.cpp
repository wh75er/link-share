#include "errors.hpp"

int BaseError::get_code() const {
  return code;
}

const char* DatabaseError::from() const {
  std::string error = "Unknown error";

  switch (code) {
    case DatabaseErrorCode::CONNECTION_FAILED_ERR :
      error = "Failed to connect to database!";
      break;
    default:
      break;
  }

  char* c = new char(50);

  strcpy(c, error.c_str());

  return c;
}

const char* AddrInfoDefaultError::from() const {
  return gai_strerror(code);
}

const char* SocketDefaultError::from() const {
  return strerror(code);
}


const char* AddrInfoException::what() const noexcept {
  return error->from();
}

const char* SocketException::what() const noexcept {
  return error->from();
}

const char* ServerException::what() const noexcept {
  return error->from();
}
