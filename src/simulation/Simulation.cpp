#include "Simulation.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Constructor
Simulation::Simulation(int particles, int steps, double temperature, double box_size)
    : box(box_size), numParticles(particles), numSteps(steps), intervalSteps(1), beta(1.0 / temperature) {}

// Initialize particles
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

    // Save initial state
    std::vector<Particle> initialParticles;
    for (size_t i = 0; i < box.getParticleCount(); ++i) {
        initialParticles.push_back(box.getParticle(i));
    }
    savedSteps.push_back({0, initialParticles});
}

// Perform a single step of the simulation
void Simulation::step() {
    int i = std::rand() % numParticles;
    Particle& particle = box.getParticle(i);
    double oldX = particle.x, oldY = particle.y, oldZ = particle.z;

    // Random displacement with scaling for smoother motion
    double dx = (static_cast<double>(std::rand()) / RAND_MAX - 0.5) * 0.1;
    double dy = (static_cast<double>(std::rand()) / RAND_MAX - 0.5) * 0.1;
    double dz = (static_cast<double>(std::rand()) / RAND_MAX - 0.5) * 0.1;

    particle.move(dx, dy, dz);
    box.applyPeriodicBoundaryConditions(particle);

    // Energy calculation
    double oldEnergy = box.calculateTotalEnergy();
    particle.x = oldX, particle.y = oldY, particle.z = oldZ;
    double newEnergy = box.calculateTotalEnergy();
    double dE = newEnergy - oldEnergy;

    // Metropolis criterion
    if (dE > 0 && exp(-beta * dE) < static_cast<double>(std::rand()) / RAND_MAX) {
        particle.x = oldX, particle.y = oldY, particle.z = oldZ; // Reject move
    } else {
        particle.move(dx, dy, dz); // Accept move
    }
}

// Run simulation for a specific number of steps
void Simulation::run(int stepsToRun) {
    for (int step = 1; step <= stepsToRun; step++) {
        this->step();

        // Save state at intervals
        if (step % intervalSteps == 0 || step == numSteps) {
            std::vector<Particle> currentStepParticles;
            for (size_t i = 0; i < box.getParticleCount(); ++i) {
                currentStepParticles.push_back(box.getParticle(i));
            }
            savedSteps.push_back({step, currentStepParticles});
        }
    }
}

// Save particle states to file
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

// Get current particles (for rendering)
const std::vector<Particle>& Simulation::getCurrentParticles() const {
    return savedSteps.back().second;
}

// Setter and getter methods
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
