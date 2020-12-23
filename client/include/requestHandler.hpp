#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <vector>

#include "model.hpp"

typedef enum ExitStatus {
    SUCCESS,
    FAILURE
} ExitStatus;


class RequestHandler { 
public:
    virtual ExitStatus FillRequest(std::string action, Model& model) = 0;
    virtual ExitStatus HandleResponse(std::string& responseBody);
    virtual ExitStatus DoLogic(Model& app) = 0;
    std::string&  GetRequestToSend();
protected:
    std::string requestToSend;
};

class AddUsersReqHandler : public RequestHandler {
public:
    AddUsersReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model& app);
private:
    std::vector<std::string> users;
};

class RemoveUsersReqHandler : public RequestHandler {
public:
    RemoveUsersReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model& app);
private:
std::vector<std::string> users;
    
};

class AddLinkReqHandler : public RequestHandler {
public:
    AddLinkReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model& app);
private:
    std::string linkName = "";
    std::string url = "";
};

class RemoveLinkReqHandler : public RequestHandler {
public:
    RemoveLinkReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model& app);
private:
    std::string linkName;
};

class ArchiveLinkReqHandler : public RequestHandler {
public:
    ArchiveLinkReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model& model);
    ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model& app);
private:
    std::string linkName;
    std::string body;
};

class CreateRoomReqHandler : public RequestHandler {
public:
    CreateRoomReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model& app);
private:
    std::string roomName;
    std::string roomHost;
};

class RemoveRoomReqHandler : public RequestHandler {
public:
    RemoveRoomReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model& app);
private:
    std::string roomName;
    std::string roomHost;
};
