//
// Created by kuba on 15.01.2026.
//

#ifndef FILOZOF_NAIVEPHILOSOPHER_H
#define FILOZOF_NAIVEPHILOSOPHER_H


#pragma once
#include "Philosopher.h"

class NaivePhilosopher : public Philosopher {
public:
    // Używamy konstruktora klasy bazowej
    using Philosopher::Philosopher;

    void pickupForks() override;
};


#endif //FILOZOF_NAIVEPHILOSOPHER_H
