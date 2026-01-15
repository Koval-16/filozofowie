//
// Created by kuba on 15.01.2026.
//

#ifndef FILOZOF_CONFIG_H
#define FILOZOF_CONFIG_H

#pragma once

struct SimulationConfig {
    int num_philosophers = 5;
    int duration_seconds = 10;

    int min_eat_ms = 50;
    int max_eat_ms = 150;
    int min_think_ms = 50;
    int max_think_ms = 150;
};

#endif //FILOZOF_CONFIG_H
