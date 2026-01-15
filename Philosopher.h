//
// Created by kuba on 15.01.2026.
//

#ifndef FILOZOF_PHILOSOPHER_H
#define FILOZOF_PHILOSOPHER_H


#pragma once
#include <thread>
#include <random>
#include <atomic>
#include "Fork.h"
#include "Config.h"

class Philosopher {
protected:
    int id;
    Fork& leftFork;
    Fork& rightFork;
    const SimulationConfig& config;

    int meals_eaten = 0;
    long long total_wait_time = 0;

    std::atomic<bool> running{true};
    std::thread life_thread;
    std::mt19937 rng;

    void randomSleep(int min_ms, int max_ms);

public:
    Philosopher(int id, Fork& l, Fork& r, const SimulationConfig& cfg);
    virtual ~Philosopher();

    // Metoda czysto wirtualna
    virtual void pickupForks() = 0;

    virtual void putDownForks();
    void dine();
    void start();
    void stop();

    int getId() const;
    int getMeals() const;
    long long getAvgWaitTime() const;
};


#endif //FILOZOF_PHILOSOPHER_H
