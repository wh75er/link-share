#include <vector>

#include "client.hpp"
#include "link.hpp"


class LinkImpl {
public:
    LinkImpl(std::string name, std::string url, std::string uuid);
    std::string getLinkInfo();
    void setLinkInfo();
    void addSnaphotPath(std::string path);
private:
    std::string linkname;
    std::string url;
    std::string uuid;
    std::vector<std::string> snapshotPaths;
};

LinkImpl::LinkImpl(std::string name, std::string url, std::string uuid) : linkname(std::move(name)), url(std::move(url)), uuid(std::move(uuid)) {}

std::string LinkImpl::getLinkInfo() {
    return linkname;
}

void LinkImpl::setLinkInfo() {

}

void LinkImpl::addSnaphotPath(std::string path) {
    snapshotPaths.push_back(std::move(path));
}

Link::Link(std::string& name, std::string& url, std::string& uuid) : linkImpl(new LinkImpl(name, url, uuid)){}
Link::~Link() {}

std::string Link::GetLinkInfo() {
    std::string ret = linkImpl->getLinkInfo();
    return ret;
}

void Link::addSnapshot(std::string& path) {
    linkImpl->addSnaphotPath(path);
}