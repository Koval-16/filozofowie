#include "Table.h"
#include "Config.h"

int main() {
    SimulationConfig config;
    config.num_philosophers = 5;
    config.duration_seconds = 20;

    Table table(config);
    table.runSimulation();
    table.printReport();

    return 0;
}