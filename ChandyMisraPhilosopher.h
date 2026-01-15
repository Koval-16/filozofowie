//
// Created by kuba on 15.01.2026.
//

#ifndef FILOZOF_CHANDYMISRAPHILOSOPHER_H
#define FILOZOF_CHANDYMISRAPHILOSOPHER_H

#pragma once
#include "Philosopher.h"
#include <mutex>
#include <condition_variable>

class ChandyMisraPhilosopher : public Philosopher {
private:
    // Wskaźniki na sąsiadów (potrzebne do komunikacji)
    ChandyMisraPhilosopher* neighborLeft = nullptr;
    ChandyMisraPhilosopher* neighborRight = nullptr;

    // Stan wewnętrzny (chroniony przez my_mutex)
    std::mutex my_mutex;
    std::condition_variable my_cv;

    // Struktura opisująca stan dla każdego z dwóch widelców (0=Lewy, 1=Prawy)
    struct ForkState {
        bool is_mine = false;       // Czy fizycznie mam widelec?
        bool is_dirty = true;       // Czy jest brudny? (Używany od ostatniego mycia)
        bool token_holder = false;  // Czy mam token (prawo do poproszenia o widelec)?
        bool request_pending = false; // Czy sąsiad poprosił mnie o ten widelec?
    };

    ForkState forks[2]; // forks[0] to lewy, forks[1] to prawy

public:
    using Philosopher::Philosopher;

    // Metoda do ustawienia sąsiadów po utworzeniu obiektów
    void setNeighbors(ChandyMisraPhilosopher* left, ChandyMisraPhilosopher* right);

    // Inicjalizacja początkowa (kto ma widelec, kto token)
    void initialSetup(int neighborLeftID, int neighborRightID);

    // Implementacja metod wirtualnych
    void pickupForks() override;
    void putDownForks() override;

    void stop() override; // <--- DODAJ TO

    // Metody komunikacyjne (wołane przez sąsiadów)
    void receiveRequest(int forkIndexFromMyPerspective);
    void receiveFork(int forkIndexFromMyPerspective);
};


#endif //FILOZOF_CHANDYMISRAPHILOSOPHER_H
