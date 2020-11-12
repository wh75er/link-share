
#include "response.hpp"


RespExitStatus LogInResp::buildResponse(std::string& responseBody) {return RESP_SUCCESS;}
RespExitStatus LogInResp::doLogic(const Request& req, Application& app) {return RESP_SUCCESS;}


RespExitStatus LogOutResp::buildResponse(std::string& responseBody) {return RESP_SUCCESS;}
RespExitStatus LogOutResp::doLogic(const Request& req, Application& app) {return RESP_SUCCESS;}


RespExitStatus CreateRoomResp::buildResponse(std::string& responseBody) {return RESP_SUCCESS;}
RespExitStatus CreateRoomResp::doLogic(const Request& req, Application& app) {return RESP_SUCCESS;}


RespExitStatus RemoveRoomResp::buildResponse(std::string& responseBody) {return RESP_SUCCESS;}
RespExitStatus RemoveRoomResp::doLogic(const Request& req, Application& app) {return RESP_SUCCESS;}


RespExitStatus AddLinkResp::buildResponse(std::string& responseBody) {return RESP_SUCCESS;}
RespExitStatus AddLinkResp::doLogic(const Request& req, Application& app) {return RESP_SUCCESS;}


RespExitStatus RemoveLinkResp::buildResponse(std::string& responseBody) {return RESP_SUCCESS;}
RespExitStatus RemoveLinkResp::doLogic(const Request& req, Application& app) {return RESP_SUCCESS;}


RespExitStatus ArchiveLinkResp::buildResponse(std::string& responseBody) {return RESP_SUCCESS;}
RespExitStatus ArchiveLinkResp::doLogic(const Request& req, Application& app) {return RESP_SUCCESS;}


ResponseHandler::ResponseHandler() {}
responsePtr ResponseHandler::HandleInput(std::string& resposeBody) {return _LogInResp;}

