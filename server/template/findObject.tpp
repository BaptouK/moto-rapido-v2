#pragma once

#include "../include/lobby.h"
#include "../include/player.h"
#include <string>
#include <vector>

template <typename T>
T* findObject(const std::string& ID, const std::vector<T*>& list) {
    for (T* obj : list) {
        if (obj->getID() == ID) {
            return obj;
        }
    }
    return nullptr;
}