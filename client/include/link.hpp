#pragma once
#include <memory>

class LinkImpl;

class Link {
public:
    Link(std::string& name, std::string& url, std::string& uuid);
    ~Link();
    std::string GetLinkInfo();
    void SetLinkInfo();
    void addSnapshot(std::string& path);

private:
    std::shared_ptr<LinkImpl> linkImpl;
};

