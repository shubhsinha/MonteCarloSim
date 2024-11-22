#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
public:
    double x, y, z;
    Particle(double x_init = 0, double y_init = 0, double z_init = 0);
    void move(double dx, double dy, double dz);
};

#endif // PARTICLE_H
