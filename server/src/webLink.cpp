#include "webLink.hpp"

WebLink::WebLink()
  : url_(""),
    snapshotId_(""),
    user_(User()),
    tags_()
{
}

WebLink::WebLink(std::string url, std::string snapshotId, User user, std::vector<std::string> tags)
  : url_(url),
    snapshotId_(snapshotId),
    user_(user),
    tags_(tags)
{
}

void WebLink::setUrl(std::string url) {
  url_ = url;
}

void WebLink::setSnapshotId(std::string snapshotId) {
  snapshotId_ = snapshotId;
}

void WebLink::setUser(User user) {
  user_ = user;
}

void WebLink::setTags(std::vector<std::string> tags) {
  tags_ = tags;
}

std::string WebLink::getUrl() {
  return url_;
}

std::string WebLink::getSnapshotId() {
  return snapshotId_;
}

User WebLink::getUser() {
  return user_;
}

std::vector<std::string> WebLink::getTags() {
  return tags_;
}
