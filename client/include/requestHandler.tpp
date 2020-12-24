#pragma once
/* #include "requestHandler.hpp" */
#include "utils.h"


template <class ResponseParser>
std::string& RequestHandler<ResponseParser>::GetRequestToSend() {
    return requestToSend;
}

template <class ResponseParser>
ExitStatus RequestHandler<ResponseParser>::HandleResponse(std::string& responseBody) {
    try {
        RequestHandler<ResponseParser>::parser = std::make_shared<ResponseParser>(responseBody);
    }
    catch (...) {
        throw std::runtime_error("Failed to parse JSON!");
    }
    std::string error;
    if (!RequestHandler<ResponseParser>::parser->get_value("error", error)) {
        throw std::runtime_error("Failed to parse JSON!");
    }
    if (error.empty()) {
        std::cout << "success!" << std::endl;
    } else {
        return FAILURE;
    }

    return SUCCESS;
}

template <class ResponseParser>
ExitStatus AddUsersReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "users", &users);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("users", users);
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus AddUsersReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) {
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus RemoveUsersReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "users", &users);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("users", users);
    return SUCCESS;
}

//ExitStatus LogOutReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
template <class ResponseParser>
ExitStatus RemoveUsersReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }

template <class ResponseParser>
ExitStatus AddLinkReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    
    fillDataFromJson(action, "name", &linkName, "url", &url);

    std::string info = model.GetUserInfo();
    std::string login, token;
    fillDataFromJson(info, "name", &login, "uuid", &token);

    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 4, "login", login, "token", token, "name", linkName, "url", url, "description", " ");

    return SUCCESS;
}

template <class ResponseParser>
ExitStatus AddLinkReqHandler<ResponseParser>::HandleResponse(std::string &responseBody) { 
    try {
        RequestHandler<ResponseParser>::parser = std::make_shared<ResponseParser>(responseBody);
    }

    catch (...) {
        throw std::runtime_error("Failed to parse JSON!");
    }

    std::string error;
    if (!RequestHandler<ResponseParser>::parser->get_value("error", error)) {
        throw std::runtime_error("Failed to parse JSON!");
    }
    if (error.empty()) {
        (RequestHandler<ResponseParser>::parser->get_value("uuid", uuid));
        std::cout << "success!" << std::endl;
    } else {
        return FAILURE;
    }
    
    return SUCCESS;
}
template <class ResponseParser>
ExitStatus AddLinkReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) {

    std::string linkInfo = packToJsonString("name", linkName, "url", url, "uuid", uuid);
    model.AddLink(linkInfo);
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus RemoveLinkReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "name", &linkName);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("linkname", linkName);

    return SUCCESS;
}
//ExitStatus RemoveLinkReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
template <class ResponseParser>
ExitStatus RemoveLinkReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }

template <class ResponseParser>
ExitStatus ArchiveLinkReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "name", &linkName);
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
    //std::cout << action << std::endl;
    fillDataFromJson(action, "name", &roomName, "host", &roomHost);

    RequestHandler<ResponseParser>::requestToSend = packToJsonString("name", roomName, "host", roomHost);

    return SUCCESS;
}
//ExitStatus CreateRoomReqHandler::HandleResponse(std::string &responseBody) {   return SUCCESS;}
template <class ResponseParser>
ExitStatus CreateRoomReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }

template <class ResponseParser>
ExitStatus RemoveRoomReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "name", &roomName, "host", &roomHost);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("name", roomName, "host", roomHost);
    return SUCCESS;
}
//ExitStatus RemoveRoomReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }

template <class ResponseParser>
ExitStatus RemoveRoomReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }


template <class ResponseParser>
ExitStatus LogInReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "login", &login, "password", &password);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 7,"login", login, "password", password);
    
    return SUCCESS;
}
template <class ResponseParser>
ExitStatus LogInReqHandler<ResponseParser>::HandleResponse(std::string& responseBody) { 
    try {
        RequestHandler<ResponseParser>::parser = std::make_shared<ResponseParser>(responseBody);
    }
    
    catch (...) {
        throw std::runtime_error("Failed to parse JSON!");
    }

    std::string error;
    if (!RequestHandler<ResponseParser>::parser->get_value("error", error)) {
        throw std::runtime_error("Failed to parse JSON!");
    }
    if (error.empty()) {
        (RequestHandler<ResponseParser>::parser->get_value("uuid", uuid));
        std::cout << "success!" << std::endl;
    } else {
        return FAILURE;
    }

    return SUCCESS;
}

template <class ResponseParser>
ExitStatus LogInReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { 
    std::string info = packToJsonString("login", login, "password", password, "uuid", uuid);
    model.SetUserInfo(info);
    return SUCCESS;
}


template <class ResponseParser>
ExitStatus SignUpReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "login", &login, "password", &password);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("login", login, "password", password);

    return SUCCESS;
}
//ExitStatus SignUpReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }

template <class ResponseParser>
ExitStatus SignUpReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }
