#include "request.hpp"


void LogInReq::buildRequestFromInput(std::istream s) {}
std::string LogInReq::RequestToString() {return "a";}


void LogOutReq::buildRequestFromInput(std::istream s) {}
std::string LogOutReq::RequestToString() {return "a";}


void CreateRoomReq::buildRequestFromInput(std::istream s) {}
std::string CreateRoomReq::RequestToString() {return "a";}


void RemoveRoomReq::buildRequestFromInput(std::istream s) {}
std::string RemoveRoomReq::RequestToString() {return "a";}


void AddLinkReq::buildRequestFromInput(std::istream s) {}
std::string AddLinkReq::RequestToString() {return "a";}


void RemoveLinkReq::buildRequestFromInput(std::istream s) {}
std::string RemoveLinkReq::RequestToString() {return "a";}


void ArchiveLinkReq::buildRequestFromInput(std::istream s) {}
std::string ArchiveLinkReq::RequestToString() {return "a";}



RequestHandler::RequestHandler() {}
requestPtr RequestHandler::HandleInput(std::string which) {return _LogInReq;}