#pragma once
/* #include "requestHandler.hpp" */
#include "utils.h"
#include "room.hpp"
#include "userinfo.hpp"
#include "model.hpp"
#include <experimental/filesystem>
#include <fstream>


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

    std::string userInfo = model.GetUserInfoStr();
    std::string login, token;
    fillDataFromJson(userInfo, "name", &login, "uuid", &token);

    std::string roomInfo = model.GetCurrentRoomInfoStr();
    fillDataFromJson(roomInfo, "uuid", &uuid);

    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 2, "login", login, "token", token, "uuid", uuid, "users", users);
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus AddUsersReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) {
    model.AddUsers(users);
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus RemoveUsersReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "users", &users);

    std::string userInfo = model.GetUserInfoStr();
    std::string login, token;
    fillDataFromJson(userInfo, "name", &login, "uuid", &token);

    std::string roomInfo = model.GetCurrentRoomInfoStr();
    fillDataFromJson(roomInfo, "uuid", &uuid);

    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 3, "login", login, "token", token, "uuid", uuid, "users", users);
    return SUCCESS;
}

//ExitStatus LogOutReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }
template <class ResponseParser>
ExitStatus RemoveUsersReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) {
    model.RemoveUsers(users);
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus AddLinkReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    
    fillDataFromJson(action, "name", &linkName, "url", &url, "description", &description);

    std::string info = model.GetUserInfoStr();
    std::string login, token;
    fillDataFromJson(info, "name", &login, "uuid", &token);

    std::string roomInfo = model.GetCurrentRoomInfoStr();
    fillDataFromJson(roomInfo, "uuid", &uuid);

    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 4, "login", login, "token", token, "uuid", uuid, "name", linkName, "url", url, "description", description);

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
    std::shared_ptr<Link> newLink = std::make_shared<Link>(linkName, url, uuid, description);

    model.AddLink(newLink);
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus RemoveLinkReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "name", &linkName);

    std::string info = model.GetUserInfoStr();
    std::string login, token;
    fillDataFromJson(info, "name", &login, "uuid", &token);

    std::string linkInfo = model.GetLinkInfoStr(linkName);
    fillDataFromJson(linkInfo, "uuid", &uuid);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 5, "login", login, "token", token, "uuid", uuid);

    return SUCCESS;
}

template <class ResponseParser>
ExitStatus RemoveLinkReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { 
    model.RemoveLink(linkName);
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus MakeSnapshotReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "name", &linkName);

    std::string info = model.GetUserInfoStr();
    std::string login, token;
    fillDataFromJson(info, "name", &login, "uuid", &token);

    std::string linkInfo = model.GetLinkInfoStr(linkName);
    fillDataFromJson(linkInfo, "uuid", &uuid);

    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 6, "login", login, "token", token, "uuid", uuid);

    return SUCCESS;
}

template <class ResponseParser>
ExitStatus MakeSnapshotReqHandler<ResponseParser>::HandleResponse(std::string &responseBody) { 
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
ExitStatus MakeSnapshotReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) {
    model.AddSnapshotUuid(linkName, uuid);
    return SUCCESS;
}


template <class ResponseParser>
ExitStatus CreateRoomReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) { 
    fillDataFromJson(action, "name", &roomName, "private", &isPrivate);

    std::string info = model.GetUserInfoStr();
    std::string login, token;
    fillDataFromJson(info, "name", &login, "uuid", &token);
    roomHost = login;

    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 0, "login", login, "token", token, "name",
                                                                     roomName, "private", isPrivate);
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus CreateRoomReqHandler<ResponseParser>::HandleResponse(std::string &responseBody) {
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
    } else {
        return FAILURE;
    }
    std::cout << "success!" << std::endl;
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus CreateRoomReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) {
    std::shared_ptr<Room> newRoom = std::make_shared<Room>(roomName, roomHost, uuid, isPrivate);
    model.AddRoom(newRoom);
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus RemoveRoomReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "name", &roomName);

    std::string userInfo = model.GetUserInfoStr();
    std::string login, token;
    fillDataFromJson(userInfo, "name", &login, "uuid", &token);

    std::string roomInfo = model.GetRoomInfoStr(roomName);
    fillDataFromJson(roomInfo, "uuid", &uuid);

    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 1, "login", login, "token", token, "uuid", uuid);
    return SUCCESS;
}
//ExitStatus RemoveRoomReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }

template <class ResponseParser>
ExitStatus RemoveRoomReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { 
    model.RemoveRoom(roomName);
    return SUCCESS;
}


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
    } else {
        return FAILURE;
    }
    std::cout << "success!" << std::endl;
    return SUCCESS;
}

template <class ResponseParser>
ExitStatus LogInReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { 
    //std::string info = packToJsonString("login", login, "password", password, "uuid", uuid);

    std::shared_ptr<UserInfo> newUserinfo = std::make_shared<UserInfo>(login, password, uuid);

    model.SetUserInfo(newUserinfo);
    return SUCCESS;
}


template <class ResponseParser>
ExitStatus SignUpReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "login", &login, "password", &password);
    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 8, "login", login, "password", password);
    return SUCCESS;
}

//ExitStatus SignUpReqHandler::HandleResponse(std::string &responseBody) { return SUCCESS; }

template <class ResponseParser>
ExitStatus SignUpReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) { return SUCCESS; }


template <class ResponseParser>
ExitStatus DownloadSnapshotReqHandler<ResponseParser>::FillRequest(std::string action, Model<ResponseParser>& model) {
    fillDataFromJson(action, "name", &linkName, "filesdir", &filesdir);

    std::string info = model.GetUserInfoStr();
    std::string login, token;
    fillDataFromJson(info, "name", &login, "uuid", &token);

    uuid = model.GetLinkSnapshotInfoStr(linkName);

    RequestHandler<ResponseParser>::requestToSend = packToJsonString("command", 9, "login", login, "token", token, "uuid", uuid);

    return SUCCESS;
}

/* template <class ResponseParser>
ExitStatus MakeSnapshotReqHandler<ResponseParser>::HandleResponse(std::string &responseBody) { 
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
        (RequestHandler<ResponseParser>::parser->get_value("files_dir", filesdir));
        std::cout << "success!" << std::endl;
    } else {
        return FAILURE;
    }

    return SUCCESS;
} */


template <class ResponseParser>
ExitStatus DownloadSnapshotReqHandler<ResponseParser>::DoLogic(Model<ResponseParser> &model) {

    return SUCCESS;
}

template <class ResponseParser>
ExitStatus DownloadSnapshotReqHandler<ResponseParser>::RecieveFile(recFile& newFile) {
    std::string mainDir(filesdir);
    std::experimental::filesystem::create_directories(mainDir);

    std::string staticDir = mainDir + "/static";
    std::experimental::filesystem::create_directories(staticDir);
    
    std::string pathToNewFile(mainDir);
    pathToNewFile += newFile.name;

    std::ofstream file(pathToNewFile, std::ios::binary);
    for (auto i : newFile.body) {
        file.write(&i, 1);
    }
    return SUCCESS;
}