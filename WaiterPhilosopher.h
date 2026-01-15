//
// Created by kuba on 15.01.2026.
//

#ifndef FILOZOF_WAITERPHILOSOPHER_H
#define FILOZOF_WAITERPHILOSOPHER_H


#pragma once
#include "Philosopher.h"
#include <mutex>

class WaiterPhilosopher : public Philosopher {
    std::mutex& waiter; // Referencja do wspólnego Kelnera

public:
    // Konstruktor przyjmuje dodatkowo referencję do kelnera
    WaiterPhilosopher(int id, Fork& l, Fork& r, const SimulationConfig& cfg, std::mutex& w);

    void pickupForks() override;
};

#endif //FILOZOF_WAITERPHILOSOPHER_H
