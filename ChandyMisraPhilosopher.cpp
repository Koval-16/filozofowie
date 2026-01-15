#include "ChandyMisraPhilosopher.h"
#include <iostream>

void ChandyMisraPhilosopher::setNeighbors(ChandyMisraPhilosopher* left, ChandyMisraPhilosopher* right) {
    neighborLeft = left;
    neighborRight = right;
}

void ChandyMisraPhilosopher::initialSetup(int leftID, int rightID) {
    // Lewy widelec (indeks 0)
    if (this->id < leftID) {
        forks[0].is_mine = true;
        forks[0].is_dirty = true;
        forks[0].token_holder = false;
    } else {
        forks[0].is_mine = false;
        forks[0].is_dirty = false;
        forks[0].token_holder = true;
    }

    // Prawy widelec (indeks 1)
    if (this->id < rightID) {
        forks[1].is_mine = true;
        forks[1].is_dirty = true;
        forks[1].token_holder = false;
    } else {
        forks[1].is_mine = false;
        forks[1].is_dirty = false;
        forks[1].token_holder = true;
    }
}

// --- POPRAWIONA METODA STOP ---
void ChandyMisraPhilosopher::stop() {
    running = false;       // Ustaw flagę
    my_cv.notify_all();    // OBUDŹ wszystkich, którzy śpią na wait()
    Philosopher::stop();   // Wywołaj oryginalne zatrzymanie (join)
}

// --- POPRAWIONE POBIERANIE WIDELCÓW ---
void ChandyMisraPhilosopher::pickupForks() {
    std::unique_lock<std::mutex> lock(my_mutex);

    // Pętla: czekaj dopóki nie masz obu widelców ORAZ program działa
    while (running && (!forks[0].is_mine || !forks[1].is_mine)) {

        // 1. Sprawdź Lewy
        if (!forks[0].is_mine && forks[0].token_holder) {
            forks[0].token_holder = false;

            // KLUCZOWE: Odblokuj mutex przed wołaniem sąsiada!
            lock.unlock();
            if(neighborLeft) neighborLeft->receiveRequest(1);
            lock.lock(); // Zablokuj z powrotem
        }

        // 2. Sprawdź Prawy
        if (!forks[1].is_mine && forks[1].token_holder) {
            forks[1].token_holder = false;

            lock.unlock(); // KLUCZOWE
            if(neighborRight) neighborRight->receiveRequest(0);
            lock.lock();
        }

        // Jeśli nadal nie mam widelców i program działa -> czekaj
        if (running && (!forks[0].is_mine || !forks[1].is_mine)) {
            my_cv.wait(lock);
        }
    }
    // Wychodzimy z pętli gdy mamy oba widelce LUB running==false
}

// --- POPRAWIONE ODKŁADANIE ---
void ChandyMisraPhilosopher::putDownForks() {
    // Zmienne pomocnicze, żeby wiedzieć komu oddać PO zwolnieniu mutexa
    bool giveLeft = false;
    bool giveRight = false;

    {
        std::lock_guard<std::mutex> lock(my_mutex);

        // Oznacz widelce jako brudne
        forks[0].is_mine = true; forks[0].is_dirty = true;
        forks[1].is_mine = true; forks[1].is_dirty = true;

        // Sprawdź czy ktoś czekał (Lewy)
        if (forks[0].request_pending) {
            forks[0].request_pending = false;
            forks[0].is_mine = false;
            forks[0].is_dirty = false;
            giveLeft = true; // Zaznacz do oddania
        }

        // Sprawdź czy ktoś czekał (Prawy)
        if (forks[1].request_pending) {
            forks[1].request_pending = false;
            forks[1].is_mine = false;
            forks[1].is_dirty = false;
            giveRight = true; // Zaznacz do oddania
        }
    } // Tutaj mutex się zwalnia!

    // Teraz bezpiecznie wołamy sąsiadów (bez trzymania własnego mutexa)
    if (giveLeft && neighborLeft) neighborLeft->receiveFork(1);
    if (giveRight && neighborRight) neighborRight->receiveFork(0);
}

// --- POPRAWIONA KOMUNIKACJA ---
void ChandyMisraPhilosopher::receiveRequest(int idx) {
    bool giveBack = false;

    {
        std::lock_guard<std::mutex> lock(my_mutex);
        forks[idx].token_holder = true; // Dostałem żądanie = mam token

        if (forks[idx].is_mine && forks[idx].is_dirty) {
            // Mam brudny widelec -> muszę go wyczyścić i oddać
            forks[idx].is_mine = false;
            forks[idx].is_dirty = false;
            giveBack = true;
        }
        else if (forks[idx].is_mine && !forks[idx].is_dirty) {
            // Mam czysty widelec (jem lub zaraz będę) -> zachowaj, ale zapamiętaj prośbę
            forks[idx].request_pending = true;
        }
        // Jeśli nie mam widelca, to nic nie robię (samo token_holder=true wystarczy)
    }

    // Oddajemy widelec po zwolnieniu mutexa
    if (giveBack) {
        if (idx == 0 && neighborLeft) neighborLeft->receiveFork(1);
        else if (idx == 1 && neighborRight) neighborRight->receiveFork(0);
    }
}

void ChandyMisraPhilosopher::receiveFork(int idx) {
    std::lock_guard<std::mutex> lock(my_mutex);

    forks[idx].is_mine = true;
    forks[idx].is_dirty = false; // Przyszedł czysty

    my_cv.notify_all(); // Powiadom wątek główny
}