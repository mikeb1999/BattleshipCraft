#include "Skybox.h"
#include <GL/glew.h>

void Skybox::render() const {
    glDisable(GL_LIGHTING);
    glColor3f(0.5f, 0.7f, 1.0f); // Light blue sky
    glBegin(GL_QUADS);
    // Simplified skybox (just a large cube for now)
    float size = 1000.0f;
    // Front face
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    // Back face
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    // Left face
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);
    // Right face
    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    // Top face
    glVertex3f(-size, size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    // Bottom face
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(-size, -size, size);
    glEnd();
    glEnable(GL_LIGHTING);
}