//
// Created by kuba on 15.01.2026.
//

#include "WaiterPhilosopher.h"

WaiterPhilosopher::WaiterPhilosopher(int id, Fork& l, Fork& r, const SimulationConfig& cfg, std::mutex& w)
        : Philosopher(id, l, r, cfg), waiter(w) {}

void WaiterPhilosopher::pickupForks() {
    // 1. Poproś Kelnera o dostęp (zablokuj mutex kelnera)
    // Używamy lock_guard, aby mutex odblokował się automatycznie na końcu tej funkcji
    std::lock_guard<std::mutex> lock(waiter);

    // TERAZ jesteśmy w strefie chronionej. Nikt inny nie może w tym momencie
    // zacząć podnosić widelców.

    // 2. Weź lewy widelec
    leftFork.mtx.lock();

    // 3. Weź prawy widelec
    rightFork.mtx.lock();

    // Koniec funkcji -> lock_guard niszczy się -> waiter.unlock()
    // Filozof trzyma teraz oba widelce, ale zwolnił Kelnera dla innych.
}