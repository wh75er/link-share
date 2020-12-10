#include <vector>

#include "client.hpp"
#include "link.hpp"


class LinkImpl {
public:
    LinkImpl(std::string name, std::string url);
    const std::string getLinkName();
    void addSnaphotPath(std::string path);
private:
    std::string linkname;
    std::string url;
    std::vector<std::string> snapshotPaths;
};

LinkImpl::LinkImpl(std::string name, std::string url) : linkname(std::move(name)), url(std::move(url)) {}

const std::string LinkImpl::getLinkName() {
    return linkname;
}

void LinkImpl::addSnaphotPath(std::string path) {
    snapshotPaths.push_back(std::move(path));
}

Link::Link(std::string& name, std::string& url) : linkImpl(new LinkImpl(name, url)){}
Link::~Link() {}

const std::string Link::GetLinkName() {
    return linkImpl->getLinkName();
}

void Link::addSnapshot(std::string& path) {
    linkImpl->addSnaphotPath(path);
}