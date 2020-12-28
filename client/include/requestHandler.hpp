#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <map>

#include "model.hpp"

typedef enum ExitStatus {
    SUCCESS,
    FAILURE
} ExitStatus;


template <class ResponseParser>
class RequestHandler { 
public:
    RequestHandler(bool recvFiles, bool servIsReq) : recievingFiles(recvFiles), servIsRequired(servIsReq) {}
    virtual ExitStatus FillRequest(std::string action, Model<ResponseParser>& model) = 0;
    virtual ExitStatus HandleResponse(std::string& responseBody);
    virtual ExitStatus DoLogic(Model<ResponseParser>& app) = 0;
    virtual ExitStatus RecieveFile(recFile& newFile) { return SUCCESS;}
    bool RecievingFiles() { return recievingFiles; }
    bool ServRequired() { return servIsRequired; }
    std::string&  GetRequestToSend();
protected:
    std::string requestToSend;
    std::shared_ptr<ResponseParser> parser;
    bool recievingFiles;
    bool servIsRequired;
};

template <class ResponseParser>
class AddUsersReqHandler : public RequestHandler<ResponseParser> {
public:
    AddUsersReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::vector<std::string> users;
    std::string uuid;
};

template <class ResponseParser>
class RemoveUsersReqHandler : public RequestHandler<ResponseParser> {
public:
    RemoveUsersReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::vector<std::string> users;
    std::string uuid;
};

template <class ResponseParser>
class AddLinkReqHandler : public RequestHandler<ResponseParser> {
public:
    AddLinkReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string uuid;
    std::string linkName;
    std::string url;
    std::string description;
};

template <class ResponseParser>
class RemoveLinkReqHandler : public RequestHandler<ResponseParser> {
public:
    RemoveLinkReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string linkName;
    std::string uuid;
};

template <class ResponseParser>
class MakeSnapshotReqHandler : public RequestHandler<ResponseParser> {
public:
    MakeSnapshotReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string linkName;
    std::string uuid;
};


template <class ResponseParser>
class CreateRoomReqHandler : public RequestHandler<ResponseParser> {
public:
    CreateRoomReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string roomName;
    std::string roomHost;
    std::string uuid;
    bool isPrivate;
};

template <class ResponseParser>
class RemoveRoomReqHandler : public RequestHandler<ResponseParser> {
public:
    RemoveRoomReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string roomName;
    std::string uuid;
};

template <class ResponseParser>
class LogInReqHandler : public RequestHandler<ResponseParser> {
public:
    LogInReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
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
    SignUpReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string login;
    std::string password;
};

template <class ResponseParser>
class DownloadSnapshotReqHandler : public RequestHandler<ResponseParser> {
public:
    DownloadSnapshotReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    //ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
    ExitStatus RecieveFile(recFile& newFile);
private:
    std::string linkName;
    std::string uuid;
    std::string filesdir;
};

template <class ResponseParser>
class GetUserRoomReqHandler : public RequestHandler<ResponseParser> {
public:
    GetUserRoomReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string uuid;
};

template <class ResponseParser>
class GetUserLinksReqHandler : public RequestHandler<ResponseParser> {
public:
    GetUserLinksReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::vector<std::map<std::string, std::string>> map;
    std::vector<Link> links;
    std::string uuid;
};

template <class ResponseParser>
class GetLinkSnapshotReqHandler : public RequestHandler<ResponseParser> {
public:
    GetLinkSnapshotReqHandler(bool recvFiles, bool servIsReq) : RequestHandler<ResponseParser>(recvFiles, servIsReq) {};
    ExitStatus FillRequest(std::string action, Model<ResponseParser>& model);
    ExitStatus HandleResponse(std::string& responseBody);
    ExitStatus DoLogic(Model<ResponseParser>& app);
private:
    std::string linkName;
    std::string uuid;
    std::vector<std::map<std::string, std::string>> map;
};

#include "requestHandler.tpp"