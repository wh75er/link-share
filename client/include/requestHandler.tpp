#pragma once
/* #include "requestHandler.hpp" */
#include "utils.h"


template <class ResponseParser>
std::string& RequestHandler<ResponseParser>::GetRequestToSend() {
    return requestToSend;
}

template <class ResponseParser>
ExitStatus RequestHandler<ResponseParser>::HandleResponse(std::string& responseBody) {
    if (responseBody.find("success") != std::string::npos) {
        return SUCCESS;
    }
    return FAILURE;
}

template <class ResponseParser>
ExitStatus AddUsersReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
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

    RequestHandler<ResponseParser>::requestToSend = packToJsonString("users", users);

    return SUCCESS;
}



//ExitStatus LogInReqHandler::HandleResponse(std::string& responseBody) { return SUCCESS; }

template <class ResponseParser>
ExitStatus AddUsersReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) {
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus RemoveUsersReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "*Users*", &users);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("users", users);
    return SUCCESS;
}

//ExitStatus LogOutReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
template <class ResponseParser>
ExitStatus RemoveUsersReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }

template <class ResponseParser>
ExitStatus AddLinkReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
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
    
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("linkname", linkName, "url", url);

    return SUCCESS;
}

//ExitStatus AddLinkReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
template <class ResponseParser>
ExitStatus AddLinkReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) {

    return SUCCESS;
}


template <class ResponseParser>
ExitStatus RemoveLinkReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "*Name*", &linkName);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("linkname", linkName);

    return SUCCESS;
}
//ExitStatus RemoveLinkReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
template <class ResponseParser>
ExitStatus RemoveLinkReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }

template <class ResponseParser>
ExitStatus ArchiveLinkReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "*Name*", &linkName);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("linkname", linkName);

    return SUCCESS;
}

template <class ResponseParser>
ExitStatus ArchiveLinkReqHandler<ResponseParser>::HandleResponse(std::string &responseBody) { 
    /* if (responseBody.find("success") == std::string::npos) {
        return FAILURE;
    }
    size_t bodyStartpos = sizeof("success");

    body = responseBody.substr(++bodyStartpos, responseBody.size()); */
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus ArchiveLinkReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }

template <class ResponseParser>
ExitStatus CreateRoomReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) { 
    fillDataFromJson(action, "*Name*", &roomName, "*Host*", &roomHost);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("name", roomName, "host", roomHost);

    return SUCCESS;
}
//ExitStatus CreateRoomReqHandler::HandleResponse(std::string &responseBody) {   return SUCCESS;}
template <class ResponseParser>
ExitStatus CreateRoomReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }

template <class ResponseParser>
ExitStatus RemoveRoomReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "*Name*", &roomName, "*Host*", &roomHost);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("name", roomName, "host", roomHost);
    return SUCCESS;
}
//ExitStatus RemoveRoomReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }

template <class ResponseParser>
ExitStatus RemoveRoomReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }

