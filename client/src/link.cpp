#include <vector>

#include "client.hpp"
#include "link.hpp"
#include "utils.h"


class LinkImpl {
public:
    LinkImpl(std::string name, std::string url, std::string uuid, std::string description);
    std::string getLinkName();
    std::string getLinkInfo();
    std::string getSnapshotUuid();
    void setLinkInfo();
    void addSnaphot(const std::string& uuid);
private:
    std::string linkname;
    std::string url;
    std::string uuid;
    std::string description;
    std::string snapshotPath;
};

LinkImpl::LinkImpl(std::string name, std::string url, std::string uuid, std::string description)
: linkname(std::move(name)),
url(std::move(url)),
uuid(std::move(uuid)),
description(std::move(description)) {}

std::string LinkImpl::getLinkName() {
    return linkname;
}

std::string LinkImpl::getLinkInfo() {
    std::string ret = packToJsonString("linkname", linkname, "url", url, "uuid", uuid, "description", description);
    return ret;
}

std::string LinkImpl::getSnapshotUuid() {
    std::string ret = snapshotPath;
    return ret;
}

void LinkImpl::setLinkInfo() {

}

void LinkImpl::addSnaphot(const std::string& uuid) {
    snapshotPath = uuid;
}

Link::Link(std::string& name, std::string& url, std::string& uuid, std::string& description)
: linkImpl(new LinkImpl(name, url, uuid, description)){}
Link::~Link() {}


std::string Link::GetLinkName() {
    std::string ret = linkImpl->getLinkName();
    return ret;
}

std::string Link::GetLinkInfo() {
    std::string ret = linkImpl->getLinkInfo();
    return ret;
}

std::string Link::GetSnapshotUuid() {
    std::string ret = linkImpl->getSnapshotUuid();
    return ret;
}

void Link::AddSnapshot(const std::string& uuid) {
    linkImpl->addSnaphot(uuid);
}

