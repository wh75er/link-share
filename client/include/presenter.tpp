/* #include "presenter.hpp" */
#pragma once

#include <string>
#include <iostream>

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
        std::string response = client.readFromServer();

        std::cout << std::endl << response << std::endl;

        model.HandleResponse(response);
        action = view.GetRequest();
        disconnect();
    }
}