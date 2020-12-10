#pragma once

#include <string>

#include "requestForm.hpp"

class IView {
public:
    virtual ~IView() = 0;
};


class ConsoleView : public IView {
public:
    ConsoleView() = default;
    ~ConsoleView() = default;
    std::string GetRequest();
    void PrintCommands();
};