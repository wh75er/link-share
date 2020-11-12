#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <application.hpp>
#include <request.hpp>

typedef enum RespExitStatus {
    RESP_SUCCESS,
    RESP_FAILURE
}RespExitStatus;


class Response {
public:
    virtual RespExitStatus buildResponse(std::string& responseBody) = 0;
    virtual RespExitStatus doLogic(const Request& req, Application& app) = 0;
};

class LogInResp : public Response{
public:
    RespExitStatus buildResponse(std::string& responseBody) override;
    RespExitStatus doLogic(const Request& req, Application& app) override;
};

class LogOutResp : public Response{
public:
    RespExitStatus buildResponse(std::string& responseBody) override;
    RespExitStatus doLogic(const Request& req, Application& app) override;
};

class CreateRoomResp : public Response{
public:
    RespExitStatus buildResponse(std::string& responseBody) override;
    RespExitStatus doLogic(const Request& req, Application& app) override;
};

class RemoveRoomResp : public Response{
public:
    RespExitStatus buildResponse(std::string& responseBody) override;
    RespExitStatus doLogic(const Request& req, Application& app) override;
};

class AddLinkResp : public Response{
public:
    RespExitStatus buildResponse(std::string& responseBody) override;
    RespExitStatus doLogic(const Request& req, Application& app) override;
};

class RemoveLinkResp : public Response{
public:
    RespExitStatus buildResponse(std::string& responseBody) override;
    RespExitStatus doLogic(const Request& req, Application& app) override;
};

class ArchiveLinkResp : public Response{
public:
    RespExitStatus buildResponse(std::string& responseBody) override;
    RespExitStatus doLogic(const Request& req, Application& app) override;
private:
    std::string body;
};


using responsePtr = std::shared_ptr<Response>;

class ResponseHandler {
public:
    ResponseHandler();
    responsePtr HandleInput(std::string& resposeBody);
private:
    responsePtr _LogInResp;
    responsePtr _LogOutResp;
    responsePtr _CreateRoomResp;
    responsePtr _RemoveRoomResp;
    responsePtr _AddLinkResp;
    responsePtr _RemoveLinkResp;
};