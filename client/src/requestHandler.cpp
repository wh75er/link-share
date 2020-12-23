
#include <algorithm>
#include "requestHandler.hpp"
#include "utils.h"




std::string& RequestHandler::GetRequestToSend() {
    return requestToSend;
}


ExitStatus RequestHandler::HandleResponse(std::string& responseBody) {
    if (responseBody.find("success") != std::string::npos) {
        return SUCCESS;
    }
    return FAILURE;
}

ExitStatus AddUsersReqHandler::FillRequest(std::string action, Model& model) {
    //std::cout << action << std::endl;

    /* auto vec = request_split(action);
    
    for (auto it = std::find(vec.begin(), vec.end(), "*Users*") + 1; it !=  vec.end(); it++) {
        users.push_back(*it);
    } */
    /* for (auto &i : vec) {
        std::cout << i << std::endl;
    } */

    fillDataFromJson(action, "*Users*", &users);


    /* std::string kk = packToJsonString("users", users);

    auto vec2 = splitString(kk);

    for (auto &i : vec2) {
        std::cout << i << std::endl;
    } */

    requestToSend = packToJsonString("users", users);

    return SUCCESS;
}

//ExitStatus LogInReqHandler::HandleResponse(std::string& responseBody) { return SUCCESS; }
ExitStatus AddUsersReqHandler::DoLogic(Model &model) {
    return SUCCESS;
}


ExitStatus RemoveUsersReqHandler::FillRequest(std::string action, Model& model) {
    fillDataFromJson(action, "*Users*", &users);
    requestToSend = packToJsonString("users", users);
    return SUCCESS;
}

//ExitStatus LogOutReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
ExitStatus RemoveUsersReqHandler::DoLogic(Model &model) { return SUCCESS; }


ExitStatus AddLinkReqHandler::FillRequest(std::string action, Model& model) {
    /* auto vec = splitString(action);

    auto it = std::find(vec.begin(), vec.end(), "*Name*") + 1;
    if (it != vec.end()) {
        linkName = *it;
    }
    it = std::find(vec.begin(), vec.end(), "*Url*") + 1;
    if (it != vec.end()) {
        url = *it;
    } */

    //std::cout << action << std::endl;

    fillDataFromJson(action, "*Name*", &linkName, "*Url*", &url);
    //std::cout << linkName << std::endl;
    //std::cout << url << std::endl;
    
    requestToSend = packToJsonString("linkname", linkName, "url", url);

    return SUCCESS;
}

//ExitStatus AddLinkReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
ExitStatus AddLinkReqHandler::DoLogic(Model &model) {

    return SUCCESS;
}



ExitStatus RemoveLinkReqHandler::FillRequest(std::string action, Model& model) {
    fillDataFromJson(action, "*Name*", &linkName);
    requestToSend = packToJsonString("linkname", linkName);

    return SUCCESS;
}
//ExitStatus RemoveLinkReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
ExitStatus RemoveLinkReqHandler::DoLogic(Model &model) { return SUCCESS; }


ExitStatus ArchiveLinkReqHandler::FillRequest(std::string action, Model& model) {
    fillDataFromJson(action, "*Name*", &linkName);
    requestToSend = packToJsonString("linkname", linkName);

    return SUCCESS;
}
ExitStatus ArchiveLinkReqHandler::HandleResponse(std::string &responseBody) { 
    /* if (responseBody.find("success") == std::string::npos) {
        return FAILURE;
    }
    size_t bodyStartpos = sizeof("success");

    body = responseBody.substr(++bodyStartpos, responseBody.size()); */
    return SUCCESS;
}
ExitStatus ArchiveLinkReqHandler::DoLogic(Model &model) { return SUCCESS; }


ExitStatus CreateRoomReqHandler::FillRequest(std::string action, Model& model) { 
    fillDataFromJson(action, "*Name*", &roomName, "*Host*", roomHost);
    requestToSend = packToJsonString("name", roomName, "host", roomHost);

    return SUCCESS;
}
//ExitStatus CreateRoomReqHandler::HandleResponse(std::string &responseBody) {   return SUCCESS;}
ExitStatus CreateRoomReqHandler::DoLogic(Model &model) { return SUCCESS; }

ExitStatus RemoveRoomReqHandler::FillRequest(std::string action, Model& model) {
    fillDataFromJson(action, "*Name*", &roomName, "*Host*", roomHost);
    requestToSend = packToJsonString("name", roomName, "host", roomHost);
    return SUCCESS;
}
//ExitStatus RemoveRoomReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
ExitStatus RemoveRoomReqHandler::DoLogic(Model &model) { return SUCCESS; }

