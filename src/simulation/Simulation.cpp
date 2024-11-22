#include "Simulation.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Constructor (already implemented)
Simulation::Simulation(int particles, int steps, double temperature, double box_size)
    : box(box_size), numParticles(particles), numSteps(steps), intervalSteps(1), beta(1.0 / temperature) {}

// Initialize particles (already implemented)
void Simulation::initialize() {
    box.clearParticles();
    std::srand(std::time(nullptr));
    for (int i = 0; i < numParticles; i++) {
        double x = static_cast<double>(std::rand()) / RAND_MAX * box.getSize();
        double y = static_cast<double>(std::rand()) / RAND_MAX * box.getSize();
        double z = static_cast<double>(std::rand()) / RAND_MAX * box.getSize();
        box.addParticle(Particle(x, y, z));
    }
    savedSteps.clear();

    std::vector<Particle> initialParticles;
    for (size_t i = 0; i < box.getParticleCount(); ++i) {
        initialParticles.push_back(box.getParticle(i));
    }
    savedSteps.push_back({0, initialParticles});
}

// Run the simulation (already implemented)
void Simulation::run() {
    savedSteps.clear();
    std::vector<Particle> initialParticles;
    for (size_t i = 0; i < box.getParticleCount(); ++i) {
        initialParticles.push_back(box.getParticle(i));
    }
    savedSteps.push_back({0, initialParticles});

    for (int step = 1; step <= numSteps; step++) {
        int i = std::rand() % numParticles;
        Particle& particle = box.getParticle(i);
        double oldX = particle.x, oldY = particle.y, oldZ = particle.z;
        double dx = (static_cast<double>(std::rand()) / RAND_MAX - 0.5);
        double dy = (static_cast<double>(std::rand()) / RAND_MAX - 0.5);
        double dz = (static_cast<double>(std::rand()) / RAND_MAX - 0.5);
        particle.move(dx, dy, dz);
        box.applyPeriodicBoundaryConditions(particle);
        double oldEnergy = box.calculateTotalEnergy();
        particle.x = oldX, particle.y = oldY, particle.z = oldZ;
        double newEnergy = box.calculateTotalEnergy();
        double dE = newEnergy - oldEnergy;
        if (dE > 0 && exp(-beta * dE) < static_cast<double>(std::rand()) / RAND_MAX) {
            particle.x = oldX, particle.y = oldY, particle.z = oldZ;
        } else {
            particle.move(dx, dy, dz);
        }

        if (step % intervalSteps == 0 || step == numSteps) {
            std::vector<Particle> currentStepParticles;
            for (size_t i = 0; i < box.getParticleCount(); ++i) {
                currentStepParticles.push_back(box.getParticle(i));
            }
            savedSteps.push_back({step, currentStepParticles});
        }
    }
}

// Save particle states to file (already implemented)
void Simulation::saveParticles(const std::string& filename) const {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    for (const auto& stepData : savedSteps) {
        int stepNumber = stepData.first;
        const std::vector<Particle>& particles = stepData.second;

        file << "ITEM: TIMESTEP\n" << stepNumber << "\n";
        file << "ITEM: NUMBER OF ATOMS\n" << particles.size() << "\n";
        file << "ITEM: BOX BOUNDS pp pp pp\n";
        file << "0 " << box.getSize() << "\n0 " << box.getSize() << "\n0 " << box.getSize() << "\n";
        file << "ITEM: ATOMS id x y z\n";

        for (size_t i = 0; i < particles.size(); ++i) {
            const Particle& p = particles[i];
            file << (i + 1) << " " << p.x << " " << p.y << " " << p.z << "\n";
        }
    }
    file.close();
}

// Missing Getter and Setter Methods Implementation

int Simulation::getNumParticles() const {
    return numParticles;
}

void Simulation::setNumParticles(int num) {
    numParticles = num;
}

int Simulation::getNumSteps() const {
    return numSteps;
}

void Simulation::setNumSteps(int steps) {
    numSteps = steps;
}

double Simulation::getTemperature() const {
    return 1.0 / beta;
}

void Simulation::setTemperature(double temp) {
    beta = 1.0 / temp;
}

void Simulation::setIntervalSteps(int interval) {
    intervalSteps = interval;
}

Box& Simulation::getBox() {
    return box;
}
