
#include "response.hpp"


void LogInResp::buildResponse(std::string responseBody) {}
void LogInResp::doLogic(const Request& req, Application& app) {}


void LogOutResp::buildResponse(std::string responseBody) {}
void LogOutResp::doLogic(const Request& req, Application& app) {}


void CreateRoomResp::buildResponse(std::string responseBody) {}
void CreateRoomResp::doLogic(const Request& req, Application& app) {}


void RemoveRoomResp::buildResponse(std::string responseBody) {}
void RemoveRoomResp::doLogic(const Request& req, Application& app) {}


void AddLinkResp::buildResponse(std::string responseBody) {}
void AddLinkResp::doLogic(const Request& req, Application& app) {}


void RemoveLinkResp::buildResponse(std::string responseBody) {}
void RemoveLinkResp::doLogic(const Request& req, Application& app) {}


void ArchiveLinkResp::buildResponse(std::string responseBody) {}
void ArchiveLinkResp::doLogic(const Request& req, Application& app) {}





ResponseHandler::ResponseHandler() {}
responsePtr ResponseHandler::HandleInput(std::string resposeBody) {return _LogInResp;}

