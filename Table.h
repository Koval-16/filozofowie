//
// Created by kuba on 15.01.2026.
//

#ifndef FILOZOF_TABLE_H
#define FILOZOF_TABLE_H


#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "Config.h"
#include "Fork.h"
#include "Philosopher.h"

class Table {
    SimulationConfig config;
    std::vector<std::unique_ptr<Fork>> forks;
    std::vector<std::unique_ptr<Philosopher>> philosophers;
    std::mutex waiter_mutex;

public:
    Table(SimulationConfig cfg);
    void runSimulation();
    void printReport();
};


#endif //FILOZOF_TABLE_H
