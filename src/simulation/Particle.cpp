#include "Particle.h"

Particle::Particle(double x_init, double y_init, double z_init)
    : x(x_init), y(y_init), z(z_init) {}

void Particle::move(double dx, double dy, double dz) {
    x += dx;
    y += dy;
    z += dz;
}
