#include "Renderer.h"
#include "glad/glad.h"


void renderParticles(const Box& box) {
    glPointSize(5.0f);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);

    double halfBoxSize = box.getSize() / 2.0;

    for (size_t i = 0; i < box.getParticleCount(); ++i) {
        const Particle& p = box.getParticle(i);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f((p.x - halfBoxSize) / halfBoxSize, 
                   (p.y - halfBoxSize) / halfBoxSize, 
                   (p.z - halfBoxSize) / halfBoxSize);
    }

    glEnd();
}
