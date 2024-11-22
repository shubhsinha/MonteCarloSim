#include "Box.h"
#include <cmath>

Box::Box(double box_size) : size(box_size) {}

void Box::addParticle(const Particle& particle) {
    particles.push_back(particle);
}

double Box::calculateLennardJonesPotential(const Particle& p1, const Particle& p2) const {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    dx -= size * round(dx / size);
    dy -= size * round(dy / size);
    dz -= size * round(dz / size);
    double r2 = dx * dx + dy * dy + dz * dz;
    double r6 = r2 * r2 * r2;
    double r12 = r6 * r6;
    return 4 * 1.0 * (pow(1.0, 12) / r12 - pow(1.0, 6) / r6);
}

double Box::calculateTotalEnergy() const {
    double totalEnergy = 0.0;
    for (size_t i = 0; i < particles.size(); i++) {
        for (size_t j = i + 1; j < particles.size(); j++) {
            totalEnergy += calculateLennardJonesPotential(particles[i], particles[j]);
        }
    }
    return totalEnergy;
}

void Box::applyPeriodicBoundaryConditions(Particle& particle) {
    particle.x -= size * floor(particle.x / size);
    particle.y -= size * floor(particle.y / size);
    particle.z -= size * floor(particle.z / size);
}

Particle& Box::getParticle(int index) const {
    return const_cast<Particle&>(particles[index]);
}

size_t Box::getParticleCount() const {
    return particles.size();
}

double Box::getSize() const {
    return size;
}

void Box::clearParticles() {
    particles.clear();
}
