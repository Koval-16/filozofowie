#include <iostream>
#include "Table.h"
#include "Config.h"

int main() {
    SimulationConfig config;

    // --- MENU WYBORU ---
    std::cout << "=== PROBLEM UCZTUJACYCH FILOZOFOW ===" << std::endl;
    std::cout << "Wybierz wariant symulacji:" << std::endl;
    std::cout << "1. Wersja Naiwna (Deadlock)" << std::endl;
    std::cout << "2. Kelner (Arbitrator)" << std::endl;
    std::cout << "3. Hierarchia (Dijkstra)" << std::endl;
    std::cout << "4. Chandy/Misra (Distributed)" << std::endl; // <--- Opcja 4
    std::cout << "Twój wybor (1-4): ";

    int choice;
    std::cin >> choice;

    switch(choice) {
        case 1:
            config.algorithm = AlgorithmType::NAIVE;
            // Dla wersji naiwnej krótki czas, bo i tak zawiśnie
            config.duration_seconds = 5;
            break;
        case 2:
            config.algorithm = AlgorithmType::WAITER;
            config.duration_seconds = 15; // Dłuższy czas, żeby zobaczyć że działa
            break;
        case 3: // <--- OBSŁUGA WYBORU
            config.algorithm = AlgorithmType::HIERARCHY;
            config.duration_seconds = 15;
            break;
        case 4: // <--- OBSŁUGA WYBORU
            config.algorithm = AlgorithmType::CHANDY_MISRA;
            config.duration_seconds = 15;
            break;
        default:
            std::cout << "Niepoprawny wybor. Uruchamiam wersje naiwna." << std::endl;
            config.algorithm = AlgorithmType::NAIVE;
            break;
    }

    std::cout << "-------------------------------------" << std::endl;

    Table table(config);
    table.runSimulation();
    table.printReport();

    return 0;
}