#pragma once
#include <memory>

class LinkImpl;

class Link {
public:
    Link(std::string& name, std::string& url);
    ~Link();
    const std::string GetLinkName();
    void addSnapshot(std::string& path);

private:
    std::shared_ptr<LinkImpl> linkImpl;
};

