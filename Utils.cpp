//
// Created by kuba on 15.01.2026.
//

#include "Utils.h"
#include <iostream>

static std::mutex print_mutex; // Mutex widoczny tylko w tym pliku

void threadSafePrint(const std::string& msg) {
    std::lock_guard<std::mutex> lock(print_mutex);
    std::cout << msg << std::endl;
}