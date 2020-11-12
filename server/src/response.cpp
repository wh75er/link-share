#include "response.hpp"

Response::Response(enum ResponseError error, std::string token, bool hasFiles, std::string snapshotId, std::vector<std::string> fileNames)
  : error_(error),
    token_(token),
    hasFiles_(hasFiles),
    snapshotId_(snapshotId),
    fileNames_(fileNames)
{
}

void Response::setError(enum ResponseError error) {
  error_ = error;
}

void Response::setToken(std::string token) {
  token_ = token;
}

void Response::setHasFiles(bool hasFiles) {
  hasFiles_ = hasFiles;
}

void Response::setSnapshotId(std::string snapshotId) {
  snapshotId_ = snapshotId;
}

void Response::setFileNames(std::vector<std::string> fileNames) {
  fileNames_ = fileNames;
}

enum ResponseError Response::getError() {
  return error_;
}

std::string Response::getToken() {
  return token_;
}

bool Response::getHasFiles() {
  return hasFiles_;
}

std::string Response::getSnapshotId() {
  return snapshotId_;
}

std::vector<std::string> Response::getFileNames() {
  return fileNames_;
}

