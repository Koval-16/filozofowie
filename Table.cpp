//
// Created by kuba on 15.01.2026.
//

#include "Table.h"
#include "NaivePhilosopher.h"
#include "WaiterPhilosopher.h"
#include "HierarchyPhilosopher.h"
#include "ChandyMisraPhilosopher.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

Table::Table(SimulationConfig cfg) : config(cfg) {
        // 1. Tworzenie widelców
        for (int i = 0; i < config.num_philosophers; ++i) {
            forks.push_back(std::make_unique<Fork>(i));
        }

        // 2. Tworzenie filozofów zależnie od wyboru
        for (int i = 0; i < config.num_philosophers; ++i) {
            Fork& left = *forks[i];
            Fork& right = *forks[(i + 1) % config.num_philosophers];

            // --- TUTAJ JEST LOGIKA WYBORU ---
            switch (config.algorithm) {
                case AlgorithmType::NAIVE:
                    // Tworzymy wersję psującą się
                    philosophers.push_back(std::make_unique<NaivePhilosopher>(i, left, right, config));
                    break;

                case AlgorithmType::WAITER:
                    // Tworzymy wersję z Kelnerem (wymaga mutexu kelnera)
                    philosophers.push_back(std::make_unique<WaiterPhilosopher>(i, left, right, config, waiter_mutex));
                    break;

                case AlgorithmType::HIERARCHY: // <--- NOWY PRZYPADEK
                    philosophers.push_back(std::make_unique<HierarchyPhilosopher>(i, left, right, config));
                    break;

                case AlgorithmType::CHANDY_MISRA:
                    philosophers.push_back(std::make_unique<ChandyMisraPhilosopher>(i, left, right, config));
                    break;
            }
        }
    if (config.algorithm == AlgorithmType::CHANDY_MISRA) {
        for (int i = 0; i < config.num_philosophers; ++i) {
            auto current = dynamic_cast<ChandyMisraPhilosopher*>(philosophers[i].get());
            int leftIdx = (i == 0) ? config.num_philosophers - 1 : i - 1; // Zawijanie w lewo
            int rightIdx = (i + 1) % config.num_philosophers;             // Zawijanie w prawo
            auto leftNeighbor = dynamic_cast<ChandyMisraPhilosopher*>(philosophers[leftIdx].get());
            auto rightNeighbor = dynamic_cast<ChandyMisraPhilosopher*>(philosophers[rightIdx].get());
            if (current && leftNeighbor && rightNeighbor) {
                current->setNeighbors(leftNeighbor, rightNeighbor);
                current->initialSetup(leftNeighbor->getId(), rightNeighbor->getId());
            }
        }
    }
}

void Table::runSimulation() {
    std::cout << "=== Start Symulacji ===" << std::endl;

    for (auto& p : philosophers) p->start();

    // Czekanie na koniec czasu symulacji
    for(int i=0; i < config.duration_seconds; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\nCzas minal! Generowanie raportu..." << std::endl;

    printReport();

    std::cout << "\nZamykanie watkow..." << std::endl;
    for (auto& p : philosophers) {
        p->stop();
    }
}

void Table::printReport() {
    std::cout << "\n=== RAPORT ===" << std::endl;
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(15) << "Posilki"
              << std::setw(20) << "Czekanie (ms)" << std::endl;

    int total = 0;
    for (const auto& p : philosophers) {
        std::cout << std::left << std::setw(10) << p->getId()
                  << std::setw(15) << p->getMeals()
                  << std::setw(20) << p->getAvgWaitTime() << std::endl;
        total += p->getMeals();
    }

    if (total == 0) {
        std::cout << "\n!!! DEADLOCK WYKRYTY !!!" << std::endl;
        std::cout << "(Wszyscy filozofowie maja 0 posilkow i wisza na widelcach)" << std::endl;
    }
}