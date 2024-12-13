#include "Renderer.h"
#include "glad/glad.h"

void renderParticles(const Box& box) {
    glPointSize(5.0f);  // Set particle size
    glEnable(GL_POINT_SMOOTH);  // Enable smooth round points
    glBegin(GL_POINTS);

    double halfBoxSize = box.getSize() / 2.0;

    // Set particle color to orange (RGB: 1.0, 0.5, 0.0)
    for (size_t i = 0; i < box.getParticleCount(); ++i) {
        const Particle& p = box.getParticle(i);
        glColor3f(1.0f, 0.5f, 0.0f);  // Orange color
        glVertex3f((p.x - halfBoxSize) / halfBoxSize,
                   (p.y - halfBoxSize) / halfBoxSize,
                   (p.z - halfBoxSize) / halfBoxSize);
    }

    glEnd();
}
