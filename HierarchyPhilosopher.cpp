#include "HierarchyPhilosopher.h"
#include <algorithm> // do std::swap

void HierarchyPhilosopher::pickupForks() {
    // Ustalamy kolejność: najpierw mniejszy ID, potem większy ID.
    Fork* first = &leftFork;
    Fork* second = &rightFork;

    if (first->id > second->id) {
        std::swap(first, second);
    }

    // 1. Zablokuj widelec o niższym numerze
    first->mtx.lock();

    // 2. Zablokuj widelec o wyższym numerze
    second->mtx.lock();

    // Dzięki temu, ostatni filozof (który ma np. widelce 4 i 0)
    // najpierw spróbuje wziąć 0. Jeśli 0 jest zajęte przez pierwszego filozofa,
    // to ostatni filozof CZEKA na 0 i nie blokuje widelca 4.
}