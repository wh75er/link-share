#pragma once
#include <memory>

class LinkImpl;

class Link {
public:
    Link(std::string& name, std::string& url, std::string& uuid, std::string& description);
    ~Link();
    std::string GetLinkName();
    std::string GetLinkInfo();
    std::string GetSnapshotUuid();
    void SetLinkInfo();
    void AddSnapshot(const std::string& uuid);
private:
    std::shared_ptr<LinkImpl> linkImpl;
};

