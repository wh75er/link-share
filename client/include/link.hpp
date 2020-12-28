#pragma once
#include <memory>

class LinkImpl;

class Link {
public:
    Link(std::string& name, std::string& url, std::string& uuid, std::string& description);
    Link(Link& link);
    ~Link();
    std::string GetLinkName();
    std::string GetLinkInfo();
    std::shared_ptr<LinkImpl>  getLinkImpl();
    std::string GetSnapshotUuid();
    void SetLinkInfo();
    void AddSnapshot(const std::string& uuid);
private:
    std::shared_ptr<LinkImpl> linkImpl;
};

