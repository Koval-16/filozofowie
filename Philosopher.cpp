//
// Created by kuba on 15.01.2026.
//

#include "Philosopher.h"
#include "Utils.h"
#include <chrono>
#include <iostream>

Philosopher::Philosopher(int id, Fork& l, Fork& r, const SimulationConfig& cfg)
        : id(id), leftFork(l), rightFork(r), config(cfg) {
    // Inicjalizacja generatora losowego
    rng.seed(std::random_device{}());
}

Philosopher::~Philosopher() {
    stop();
}

void Philosopher::randomSleep(int min_ms, int max_ms) {
    std::uniform_int_distribution<int> dist(min_ms, max_ms);
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng)));
}

void Philosopher::putDownForks() {
    leftFork.mtx.unlock();
    rightFork.mtx.unlock();
}

void Philosopher::dine() {
    while (running) {
        // 1. Myślenie
        randomSleep(config.min_think_ms, config.max_think_ms);
        if (!running) break;

        // 2. Oczekiwanie i branie widelców
        auto start_wait = std::chrono::high_resolution_clock::now();
        pickupForks();
        auto end_wait = std::chrono::high_resolution_clock::now();

        total_wait_time += std::chrono::duration_cast<std::chrono::milliseconds>(end_wait - start_wait).count();

        // 3. Jedzenie
        threadSafePrint("Filozof " + std::to_string(id) + " JE.");
        randomSleep(config.min_eat_ms, config.max_eat_ms);
        meals_eaten++;

        // 4. Odkładanie
        putDownForks();
    }
}

void Philosopher::start() {
    running = true;
    life_thread = std::thread(&Philosopher::dine, this);
}

void Philosopher::stop() {
    running = false;
    if (life_thread.joinable()) {
        life_thread.join();
    }
}

int Philosopher::getId() const { return id; }
int Philosopher::getMeals() const { return meals_eaten; }
long long Philosopher::getAvgWaitTime() const {
    return meals_eaten == 0 ? 0 : total_wait_time / meals_eaten;
}