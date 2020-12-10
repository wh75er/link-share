
#include "requestHandler.hpp"

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
    size_t separator = action.find("*Users*") + sizeof("*Users*");

    std::string subStr = action.substr(separator, action.size() - separator);
    while(subStr.size()) {
        separator = subStr.find_first_of(",");

        users.push_back(subStr.substr(0, separator - 1));
        subStr = subStr.substr(separator, action.size());
    }

    requestToSend += "3," + model.GetMainRoomInfo();
    for(std::vector<std::string>::iterator it = users.begin(); it != users.end(); ++it) {
        requestToSend += "," + (*it); 
    }

    return SUCCESS;
}

//ExitStatus LogInReqHandler::HandleResponse(std::string& responseBody) { return SUCCESS; }
ExitStatus AddUsersReqHandler::DoLogic(Model &model) {
    return SUCCESS;
}


ExitStatus RemoveUsersReqHandler::FillRequest(std::string action, Model& model) {
    size_t separator = action.find("*Users*") + sizeof("*Users*");

    std::string subStr = action.substr(separator, action.size());
    while(subStr.size()) {
        separator = subStr.find_first_of(",");

        users.push_back(subStr.substr(0, separator - 1));
        subStr = subStr.substr(separator, action.size());
    }

    requestToSend += "3," + model.GetMainRoomInfo();
    for(std::vector<std::string>::iterator it = users.begin(); it != users.end(); ++it) {
        requestToSend += "," + (*it); 
    }
    return SUCCESS;
}

//ExitStatus LogOutReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
ExitStatus RemoveUsersReqHandler::DoLogic(Model &model) { return SUCCESS; }


ExitStatus AddLinkReqHandler::FillRequest(std::string action, Model& model) {
    size_t separator1 = action.find("*Name*") + sizeof("*Name*");
    size_t separator2 = action.find("*Url*");
    linkName = action.substr(separator1, separator2 - (separator1));
    url = action.substr(separator2 + sizeof("*Url*"), action.size());

    requestToSend += "3," + linkName +  "," + url;

    return SUCCESS;
}

//ExitStatus AddLinkReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
ExitStatus AddLinkReqHandler::DoLogic(Model &model) {

    return SUCCESS;
}



ExitStatus RemoveLinkReqHandler::FillRequest(std::string action, Model& model) {
    size_t separator = action.find("*Name*") + sizeof("*Name*");
    linkName = action.substr(separator, action.size());
    
    requestToSend += "3," + linkName;

    return SUCCESS;
}
//ExitStatus RemoveLinkReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
ExitStatus RemoveLinkReqHandler::DoLogic(Model &model) { return SUCCESS; }


ExitStatus ArchiveLinkReqHandler::FillRequest(std::string action, Model& model) {
    size_t separator = action.find("*Name*") + sizeof("*Name*");
    linkName = action.substr(separator, action.size() - separator);
    
    requestToSend = "3," + linkName;

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
    size_t separator1 = action.find("*Name*") + sizeof("*Name*");
    size_t separator2 = action.find("*Host*");
    roomName = action.substr(separator1 - 1, separator2 - (separator1 - 1));
    roomHost = action.substr(separator2 + sizeof("*Host*") - 1, action.size());

    requestToSend += "1," + roomHost +  "," + roomName;

    return SUCCESS;
}
//ExitStatus CreateRoomReqHandler::HandleResponse(std::string &responseBody) {   return SUCCESS;}
ExitStatus CreateRoomReqHandler::DoLogic(Model &model) { return SUCCESS; }

ExitStatus RemoveRoomReqHandler::FillRequest(std::string action, Model& model) {
    size_t separator1 = action.find("*Name*") + sizeof("*Name*");
    size_t separator2 = action.find("*Host*");
    roomName = action.substr(separator1 - 1, separator2 - (separator1 - 1));
    roomHost = action.substr(separator2 + sizeof("*Host*") - 1, action.size());

    requestToSend = "2," + roomHost +  "," + roomName;

    return SUCCESS;
}
//ExitStatus RemoveRoomReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
ExitStatus RemoveRoomReqHandler::DoLogic(Model &model) { return SUCCESS; }

