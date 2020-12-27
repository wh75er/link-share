/* #include "presenter.hpp" */
#pragma once

#include <string>
#include <iostream>

#include "requestHandler.hpp"

template <class ResponseParser>
Presenter<ResponseParser>::Presenter(const std::string& host, const size_t port) :
client(host, port) { /* client.Connect(); */}

template <class ResponseParser>
Presenter<ResponseParser>::~Presenter() {
}

template <class ResponseParser>
void Presenter<ResponseParser>::connect() {
    client.Connect();
}

template <class ResponseParser>
void Presenter<ResponseParser>::disconnect() {
    client.Close();
}

template <class ResponseParser>
void Presenter<ResponseParser>::run() {
    std::string action = view.GetRequest();
    while(!action.empty()) {
        connect();
        std::string request = model.FormRequest(action);
        client.writeToServer(request);
        bool endFlag = false;
        std::string response = client.readFromServer(&endFlag);

        std::cout << std::endl << response << std::endl;
        
        model.HandleResponse(response);
        while(!endFlag) {
            if (model.IsHandlerRecievingFiles()) {
                recFile newFile;
                newFile.name = client.readFromServer(&endFlag);
                newFile.body = client.readFileBodyFromServer(&endFlag);
                std::cout << newFile.body.size() << std::endl;
                model.HandleFile(newFile);
            } else {
                std::string response = client.readFromServer(&endFlag);

                std::cout << std::endl << response << std::endl;

                model.HandleResponse(response);
            }
        }
        action = view.GetRequest();
        disconnect();
    }
}