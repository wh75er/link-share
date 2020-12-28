#pragma once

#include <memory>

#include "client.hpp"
#include "model.hpp"
#include "view.hpp"

template <class ResponseParser>
class Presenter {
public:
    Presenter(const std::string& host, const size_t port);
    Presenter(Presenter& pr) = delete;
    void connect();
    void disconnect();
    Presenter& operator=(Presenter& pr) = delete;
    ~Presenter();
    void run();
private:
    Client client;
    Model<ResponseParser> model;
    ConsoleView view;
};

#include "presenter.tpp"