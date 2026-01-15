//
// Created by kuba on 15.01.2026.
//

#include "NaivePhilosopher.h"
#include <thread>
#include <chrono>

void NaivePhilosopher::pickupForks() {
    leftFork.mtx.lock();

    // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // <--- WYŁĄCZ TO
    // Zamiast tego, dajmy szansę losowi - malutkie, losowe opóźnienie:
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    rightFork.mtx.lock();
}