#ifndef FILOZOF_FORK_H
#define FILOZOF_FORK_H


#pragma once
#include <mutex>

class Fork {
public:
    int id;
    std::mutex mtx;

    Fork(int id);

    // Blokada kopiowania
    Fork(const Fork&) = delete;
    Fork& operator=(const Fork&) = delete;
};


#endif //FILOZOF_FORK_H
