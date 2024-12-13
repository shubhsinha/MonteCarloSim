#ifndef SIMULATION_H
#define SIMULATION_H

#include "Box.h"
#include <vector>
#include <deque>
#include <string>

class Simulation {
private:
    Box box;
    int numParticles;
    int numSteps;
    int intervalSteps;
    double beta;
    std::deque<std::pair<int, std::vector<Particle>>> savedSteps;

public:
    Simulation(int particles, int steps, double temperature, double box_size);

    // Initialization and execution
    void initialize();
    void step();                      // Perform a single simulation step
    void run(int stepsToRun = 1);     // Run a specific number of steps

    // Data saving and retrieval
    void saveParticles(const std::string& filename) const;
    const std::vector<Particle>& getCurrentParticles() const; // Get current particle states for rendering

    // Parameter setters and getters
    void setIntervalSteps(int interval);
    int getNumParticles() const;
    void setNumParticles(int num);
    int getNumSteps() const;
    void setNumSteps(int steps);
    double getTemperature() const;
    void setTemperature(double temp);

    // Access to the simulation box
    Box& getBox();
};

#endif // SIMULATION_H
