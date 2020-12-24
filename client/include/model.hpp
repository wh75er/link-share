#pragma once

#include <memory>

//#include "client.hpp"
template <class ResponseParser>
class ModelImpl;

template <class ResponseParser>
class Model {
public:
    Model();
    ~Model();
    std::string GetMainRoomInfo();
    //void PassAction(std::string& action);
    void SetUserInfo(const std::string& str);
    std::string GetUserInfo();
    void AddLink(std::string& linkInfo);
    std::string FormRequest(std::string& action);
    void HandleResponse(std::string& response);
private:
    std::shared_ptr<ModelImpl<ResponseParser>> modelImpl;
};

#include "model.tpp"