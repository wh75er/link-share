#include "presenter.hpp"

#include <iostream>

Presenter::Presenter() {
}

Presenter::~Presenter() {
}

void Presenter::run() {
    std::string action = view.GetRequest();
    while(!action.empty()) {
        model.PassAction(action);
        action = view.GetRequest();
    }
}