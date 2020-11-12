
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <application.hpp>
#include <request.hpp>

class Response {
public:
    virtual void buildResponse(std::string responseBody) = 0;
    virtual void doLogic(const Request& req, Application& app) = 0;
};

class LogInResp : public Response{
public:
    void buildResponse(std::string responseBody) override;
    void doLogic(const Request& req, Application& app) override;
};

class LogOutResp : public Response{
public:
    void buildResponse(std::string responseBody) override;
    void doLogic(const Request& req, Application& app) override;
};

class CreateRoomResp : public Response{
public:
    void buildResponse(std::string responseBody) override;
    void doLogic(const Request& req, Application& app) override;
};

class RemoveRoomResp : public Response{
public:
    void buildResponse(std::string responseBody) override;
    void doLogic(const Request& req, Application& app) override;
};

class AddLinkResp : public Response{
public:
    void buildResponse(std::string responseBody) override;
    void doLogic(const Request& req, Application& app) override;
};

class RemoveLinkResp : public Response{
public:
    void buildResponse(std::string responseBody) override;
    void doLogic(const Request& req, Application& app) override;
};

class ArchiveLinkResp : public Response{
public:
    void buildResponse(std::string responseBody) override;
    void doLogic(const Request& req, Application& app) override;
private:
    std::string body;
};


using responsePtr = std::shared_ptr<Response>;

class ResponseHandler {
public:
    ResponseHandler();
    responsePtr HandleInput(std::string resposeBody);
private:
    responsePtr _LogInResp;
    responsePtr _LogOutResp;
    responsePtr _CreateRoomResp;
    responsePtr _RemoveRoomResp;
    responsePtr _AddLinkResp;
    responsePtr _RemoveLinkResp;
};