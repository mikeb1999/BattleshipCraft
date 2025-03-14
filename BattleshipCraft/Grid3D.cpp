


#include "Grid3D.h"
#include <GL/glew.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Grid3D::render() const {
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 0.3f); // Gray grid lines
    glBegin(GL_LINES);

    // Draw X-axis lines (horizontal)
    for (int x = -50; x <= 50; x += 1) {
        glVertex3f(static_cast<GLfloat>(x), 0.0f, static_cast<GLfloat>(-50));
        glVertex3f(static_cast<GLfloat>(x), 0.0f, static_cast<GLfloat>(50));
    }

    // Draw Z-axis lines (depth)
    for (int z = -50; z <= 50; z += 1) {
        glVertex3f(static_cast<GLfloat>(-50), 0.0f, static_cast<GLfloat>(z));
        glVertex3f(static_cast<GLfloat>(50), 0.0f, static_cast<GLfloat>(z));
    }

    glEnd();
    glEnable(GL_LIGHTING);

    // Draw axes (red X, green Y, blue Z)
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // X-axis (red)
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Y-axis (green)
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Z-axis (blue)
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
}