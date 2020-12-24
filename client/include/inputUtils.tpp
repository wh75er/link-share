#pragma once

#include <iostream>

template<typename T, typename... Args>
void writeData(T* key) {
    fillObject(key);
}

template<typename T, typename... Args>
void writeData(T* key, Args... args) {
    fillObject(key);
    writeData(args...);
}