#ifndef BOX_H
#define BOX_H

#include <cstddef>  // Add this line to include size_t
#include <vector>
#include "Particle.h"

class Box {
private:
    double size;
    std::vector<Particle> particles;

public:
    Box(double box_size);
    void addParticle(const Particle& particle);
    double calculateLennardJonesPotential(const Particle& p1, const Particle& p2) const;
    double calculateTotalEnergy() const;
    void applyPeriodicBoundaryConditions(Particle& particle);
    Particle& getParticle(int index) const;
    size_t getParticleCount() const;  // Now size_t is properly defined
    double getSize() const;
    void clearParticles();
};

#endif // BOX_H
