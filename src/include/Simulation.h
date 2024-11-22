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
    void initialize();
    void run();
    void saveParticles(const std::string& filename) const;
    void setIntervalSteps(int interval);
    int getNumParticles() const;
    void setNumParticles(int num);
    int getNumSteps() const;
    void setNumSteps(int steps);
    double getTemperature() const;
    void setTemperature(double temp);
    Box& getBox();
};

#endif // SIMULATION_H
