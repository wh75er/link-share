#pragma once

#include <memory>

#include "client.hpp"
#include "requestForm.hpp"


class ModelImpl;


class Model {
public:
    Model();
    ~Model();
    std::string GetMainRoomInfo();
    void PassAction(std::string& action);

private:
    std::shared_ptr<ModelImpl> modelImpl;
};