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

template <class ResponseParser>
class RequestHandler { 
public:
    virtual ExitStatus FillRequest(std::string action, Model<ResponseParser>& model) = 0;
    virtual ExitStatus HandleResponse(std::string& responseBody);
    virtual ExitStatus DoLogic(Model<ResponseParser>& app) = 0;
    std::string&  GetRequestToSend();
protected:
    std::string requestToSend;
    std::shared_ptr<ResponseParser> parser;
};

template <class ResponseParser>
class AddUsersReqHandler : public RequestHandler<ResponseParser> {
public:
    AddUsersReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::vector<std::string> users;
};

template <class ResponseParser>
class RemoveUsersReqHandler : public RequestHandler<ResponseParser> {
public:
    RemoveUsersReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
std::vector<std::string> users;
    
};

template <class ResponseParser>
class AddLinkReqHandler : public RequestHandler<ResponseParser> {
public:
    AddLinkReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string linkName = "";
    std::string url = "";
};

template <class ResponseParser>
class RemoveLinkReqHandler : public RequestHandler<ResponseParser> {
public:
    RemoveLinkReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string linkName;
};

template <class ResponseParser>
class ArchiveLinkReqHandler : public RequestHandler<ResponseParser> {
public:
    ArchiveLinkReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string linkName;
    std::string body;
};

template <class ResponseParser>
class CreateRoomReqHandler : public RequestHandler<ResponseParser> {
public:
    CreateRoomReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string roomName;
    std::string roomHost;
};

template <class ResponseParser>
class RemoveRoomReqHandler : public RequestHandler<ResponseParser> {
public:
    RemoveRoomReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string roomName;
    std::string roomHost;
};

template <class ResponseParser>
class LogInReqHandler : public RequestHandler<ResponseParser> {
public:
    LogInReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string uuid;
    std::string login;
    std::string password;
};

template <class ResponseParser>
class SignUpReqHandler : public RequestHandler<ResponseParser> {
public:
    SignUpReqHandler() = default;
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string login;
    std::string password;
};

#include "requestHandler.tpp"