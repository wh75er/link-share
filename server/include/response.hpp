#pragma once

#include <string>
#include <vector>

enum ResponseError {
  SUCCESS=0,
  ERROR,
};

class Response {
public:
  Response(enum ResponseError error, std::string token, bool hasFiles, std::string snapshotId, std::vector<std::string> fileNames);
  ~Response() {};

  void setError(enum ResponseError error);
  void setToken(std::string token);
  void setHasFiles(bool hasFiles);
  void setSnapshotId(std::string snapshotId);
  void setFileNames(std::vector<std::string> fileNames);

  enum ResponseError getError();
  std::string getToken();
  bool getHasFiles();
  std::string getSnapshotId();
  std::vector<std::string> getFileNames();

private:
  enum ResponseError error_;
  std::string token_;
  bool hasFiles_;
  std::string snapshotId_;
  std::vector<std::string> fileNames_;
};
