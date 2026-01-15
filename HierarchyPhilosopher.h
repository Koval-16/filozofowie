//
// Created by kuba on 15.01.2026.
//

#ifndef FILOZOF_HIERARCHYPHILOSOPHER_H
#define FILOZOF_HIERARCHYPHILOSOPHER_H


#pragma once
#include "Philosopher.h"

class HierarchyPhilosopher : public Philosopher {
public:
    // Używamy konstruktora klasy bazowej
    using Philosopher::Philosopher;

    void pickupForks() override;
};

#endif //FILOZOF_HIERARCHYPHILOSOPHER_H
