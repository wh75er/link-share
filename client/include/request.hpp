#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <vector>


typedef enum ReqExitStatus {
    REQ_SUCCESS,
    REQ_FAILURE
}ReqExitStatus;


class Request {
public:
    virtual ReqExitStatus buildRequestFromInput(std::istream& s) = 0;
    virtual std::string RequestToString() = 0;
};

class LogInReq : public Request {
public:
    ReqExitStatus buildRequestFromInput(std::istream& s) override;
    std::string RequestToString() override;
private:
    std::string name;
    std::string password;
};

class LogOutReq : public Request {
public:
    ReqExitStatus buildRequestFromInput(std::istream& s) override;
    std::string RequestToString() override;
private:
};

class CreateRoomReq : public Request {
public:
    ReqExitStatus buildRequestFromInput(std::istream& s) override;
    std::string RequestToString() override;
private:
    std::string roomName;
    std::string roomHost;
    std::vector<std::string> participants;
};

class RemoveRoomReq : public Request {
public:
    ReqExitStatus buildRequestFromInput(std::istream& s) override;
    std::string RequestToString() override;
private:
    std::string name;
};

class AddLinkReq : public Request {
public:
    ReqExitStatus buildRequestFromInput(std::istream& s) override;
    std::string RequestToString() override;
private:
    std::string linkName;
    std::string url;
    std::string tag;
};

class RemoveLinkReq : public Request {
public:
    ReqExitStatus buildRequestFromInput(std::istream&s) override;
    std::string RequestToString() override;
private:
    std::string linkName;
};

class ArchiveLinkReq : public Request {
public:
    ReqExitStatus buildRequestFromInput(std::istream& s) override;
    std::string RequestToString() override;
private:
    std::string linkName;
};


using requestPtr = std::shared_ptr<Request>;

class RequestHandler {
public:
    RequestHandler();
    requestPtr HandleInput(std::string& which);
private:
    requestPtr _LogInReq;
    requestPtr _LogOutReq;
    requestPtr _CreateRoomReq;
    requestPtr _RemoveRoomReq;
    requestPtr _AddLinkReq;
    requestPtr _RemoveLinkReq;
    requestPtr _LinkReq;
    requestPtr _ArchiveLinkReq;
};