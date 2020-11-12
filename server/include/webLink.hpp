#pragma once

#include <string>
#include <vector>

#include "user.hpp"

class WebLink {
public:
  WebLink();
  WebLink(std::string url, std::string snapshotId, User user, std::vector<std::string> tags);
  ~WebLink() {};

  void setUrl(std::string url);
  void setSnapshotId(std::string snapshotId);
  void setUser(User user);
  void setTags(std::vector<std::string> tags);

  std::string getUrl();
  std::string getSnapshotId();
  User getUser();
  std::vector<std::string> getTags();

private:
  std::string url_;
  std::string snapshotId_;
  User user_;
  std::vector<std::string> tags_;
};
