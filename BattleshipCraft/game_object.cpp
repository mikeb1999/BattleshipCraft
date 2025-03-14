

#include "game_object.h"
#include "config.h"
#include <GL/glew.h>

Ground::Ground() {}

void Ground::render() const {
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue ground
    glNormal3f(0.0f, 1.0f, 0.0f); // Normal pointing up
    glVertex3f(-Config::GROUND_SIZE, -Config::GROUND_SIZE, 0.0f);
    glVertex3f(Config::GROUND_SIZE, -Config::GROUND_SIZE, 0.0f);
    glVertex3f(Config::GROUND_SIZE, Config::GROUND_SIZE, 0.0f);
    glVertex3f(-Config::GROUND_SIZE, Config::GROUND_SIZE, 0.0f);
    glEnd();

    // Add grid lines on the ground
    glColor3f(0.1f, 0.1f, 0.5f); // Darker blue grid lines
    glBegin(GL_LINES);
    for (float x = -Config::GROUND_SIZE; x <= Config::GROUND_SIZE; x += 10.0f) {
        glVertex3f(x, -Config::GROUND_SIZE, 0.001f);
        glVertex3f(x, Config::GROUND_SIZE, 0.001f);
    }
    for (float y = -Config::GROUND_SIZE; y <= Config::GROUND_SIZE; y += 10.0f) {
        glVertex3f(-Config::GROUND_SIZE, y, 0.001f);
        glVertex3f(Config::GROUND_SIZE, y, 0.001f);
    }
    glEnd();
    glPopMatrix();
}

Skybox::Skybox() {}

void Skybox::render() const {
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.4f, 0.6f); // Blue sky
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);
    glVertex3f(-Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);
    glVertex3f(-Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);
    glVertex3f(-Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);

    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);
    glVertex3f(-Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);

    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);
    glVertex3f(Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);
    glVertex3f(-Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);
    glVertex3f(-Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, Config::SKYBOX_SIZE);
    glVertex3f(-Config::SKYBOX_SIZE, Config::SKYBOX_SIZE, -Config::SKYBOX_SIZE);

    glEnd();
    glPopMatrix();
}