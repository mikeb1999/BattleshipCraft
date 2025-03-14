

#include "Ground.h"
#include <GL/glew.h>
#include "config.h"

void Ground::render() const {
    glDisable(GL_LIGHTING);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue ground
    glBegin(GL_QUADS);
    glVertex3f(-Config::GROUND_SIZE, 0.0f, -Config::GROUND_SIZE);
    glVertex3f(Config::GROUND_SIZE, 0.0f, -Config::GROUND_SIZE);
    glVertex3f(Config::GROUND_SIZE, 0.0f, Config::GROUND_SIZE);
    glVertex3f(-Config::GROUND_SIZE, 0.0f, Config::GROUND_SIZE);
    glEnd();
    glEnable(GL_LIGHTING);
}