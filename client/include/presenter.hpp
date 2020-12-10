#pragma once

#include <memory>

#include "model.hpp"
#include "view.hpp"

class Presenter {
public:
    Presenter();
    Presenter(Presenter& pr) = delete;
    Presenter& operator=(Presenter& pr) = delete;
    ~Presenter();
    void run();
private:
    Model model;
    ConsoleView view;
};