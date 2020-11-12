
#include "request.hpp"


ReqExitStatus LogInReq::buildRequestFromInput(std::istream& s) {return REQ_SUCCESS;}
std::string LogInReq::RequestToString() {return "a";}


ReqExitStatus LogOutReq::buildRequestFromInput(std::istream& s) {return REQ_SUCCESS;}
std::string LogOutReq::RequestToString() {return "a";}


ReqExitStatus CreateRoomReq::buildRequestFromInput(std::istream& s) {return REQ_SUCCESS;}
std::string CreateRoomReq::RequestToString() {return "a";}


ReqExitStatus RemoveRoomReq::buildRequestFromInput(std::istream& s) {return REQ_SUCCESS;}
std::string RemoveRoomReq::RequestToString() {return "a";}


ReqExitStatus AddLinkReq::buildRequestFromInput(std::istream& s) {return REQ_SUCCESS;}
std::string AddLinkReq::RequestToString() {return "a";}


ReqExitStatus RemoveLinkReq::buildRequestFromInput(std::istream& s) {return REQ_SUCCESS;}
std::string RemoveLinkReq::RequestToString() {return "a";}


ReqExitStatus ArchiveLinkReq::buildRequestFromInput(std::istream& s) {return REQ_SUCCESS;}
std::string ArchiveLinkReq::RequestToString() {return "a";}



RequestHandler::RequestHandler() {}
requestPtr RequestHandler::HandleInput(std::string& which) {return _LogInReq;}