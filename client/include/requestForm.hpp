#pragma once
#include <string>

struct RequestBody {std::string ff = "AAAAAAA";};

struct RequestForm {
    struct RequestBody Body;
    
    int Type;
};


struct AddLinkBody : public RequestBody {
    std::string linkName;
    std::string url;
};

struct RemoveLinkBody : public RequestBody {
    std::string linkName;
};

struct ArchiveLinkBody : public RequestBody {
    std::string linkName;
};

struct CreateRoomBody : public RequestBody {
    std::string roomName;
    std::string roomHost;
};

struct RemoveRoomBody : public RequestBody {
    std::string roomName;
};