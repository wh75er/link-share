#pragma once


#include <string>
#include <memory>
#include <iostream>


class RequestManagerImpl;
class Model;

class RequestManager {
public:
    RequestManager();
    ~RequestManager();
    RequestManager& operator=(RequestManager& manager) = delete;
    RequestManager(RequestManager& manager) = delete;
    /* void HandleInput(std::string& action, Model& model); */
private:
    void addRequest(std::string& action);
    std::shared_ptr<RequestManagerImpl> managerImpl;
};