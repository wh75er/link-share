/* #include "presenter.hpp" */
#pragma once

#include <string>
#include <iostream>

#include "utils.h"
#include "requestHandler.hpp"

template <class ResponseParser>
Presenter<ResponseParser>::Presenter(const std::string &host, const size_t port) : client(host, port)
{ /* client.Connect(); */
}

template <class ResponseParser>
Presenter<ResponseParser>::~Presenter()
{
}

template <class ResponseParser>
void Presenter<ResponseParser>::connect()
{
    client.Connect();
}

template <class ResponseParser>
void Presenter<ResponseParser>::disconnect()
{
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

        //std::cout << std::endl << response << std::endl;
        
        model.HandleResponse(response);
        while(!endFlag) {
            if (model.IsHandlerRecievingFiles()) {
                recFile newFile;
                newFile.name = client.readFromServer(&endFlag);
                //std::cout << "FILENAME: " << newFile.name.substr(0, 80) << std::endl << std::endl << std::endl;
                newFile.body = client.readFileBodyFromServer(&endFlag);

                model.HandleFile(newFile);
            } else {
                std::string response = client.readFromServer(&endFlag);

                //std::cout << std::endl << response << std::endl;

                model.HandleResponse(response);
            }
        }
        action = view.GetRequest();
        disconnect();
    }
}


/* template <class ResponseParser>
void Presenter<ResponseParser>::run()
{
    std::string action = view.GetRequest();
    bool loginFlag = false;
    std::string request, response;
    while (!action.empty())
    {
        bool endFlag = false;
        if (loginFlag)
        {
            connect();
            std::string login, token;
            fillDataFromJson(request, "login", &login);
            fillDataFromJson(response, "uuid", &token);
            action = "{\"command\": 10,\"login\": \"" + login + "\",\"token\": \"" + token + "\"}";
            request = model.FormRequest(action);
            client.writeToServer(request);
            response = client.readFromServer(&endFlag);
            model.HandleResponse(response);
            loginFlag = false;
            disconnect();
        }
        if (!loginFlag) {
            connect();
            request = model.FormRequest(action);
            client.writeToServer(request);
            response = client.readFromServer(&endFlag);
            model.HandleResponse(response);

            if (model.IsLogin())
            {
                loginFlag = true;
            }

            while (!endFlag)
            {
                if (model.IsHandlerRecievingFiles())
                {
                    recFile newFile;
                    newFile.name = client.readFromServer(&endFlag);
                    newFile.body = client.readFileBodyFromServer(&endFlag);

                    model.HandleFile(newFile);
                }
                else
                {
                    std::string response = client.readFromServer(&endFlag);

                    model.HandleResponse(response);
                }
            }
            disconnect();
        }
    action = view.GetRequest();
    }
}
 */