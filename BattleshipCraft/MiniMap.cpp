

#include "minimap.h"
#include <GL/glew.h>
#include <SDL.h>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

MiniMap::MiniMap(int width, int height, int mapSize)
    : width(width), height(height), mapSize(mapSize) {}

void MiniMap::renderBorder(int windowWidth, int windowHeight) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, static_cast<GLfloat>(windowWidth), 0, static_cast<GLfloat>(windowHeight), -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(static_cast<GLfloat>(windowWidth - width - 2), static_cast<GLfloat>(windowHeight - height - 2));
    glVertex2f(static_cast<GLfloat>(windowWidth - 2), static_cast<GLfloat>(windowHeight - height - 2));
    glVertex2f(static_cast<GLfloat>(windowWidth - 2), static_cast<GLfloat>(windowHeight - 2));
    glVertex2f(static_cast<GLfloat>(windowWidth - width - 2), static_cast<GLfloat>(windowHeight - 2));
    glEnd();
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void MiniMap::render(const MapGrid& mapGrid, const Camera& camera, const Scene& scene, int windowWidth, int windowHeight) {
    std::cout << "Setting minimap viewport: x=" << (windowWidth - width) << ", y=" << (windowHeight - height)
        << ", width=" << width << ", height=" << height << std::endl;

    glViewport(windowWidth - width, windowHeight - height, width, height);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-mapSize / 2.0f, mapSize / 2.0f, -mapSize / 2.0f, mapSize / 2.0f, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);

    // Render map grid with global coordinates
    for (int x = 0; x < mapGrid.getWidth(); ++x) {
        for (int z = 0; z < mapGrid.getDepth(); ++z) {
            Block::Type block = mapGrid.getBlock(x, 0, z);
            if (block != Block::AIR) {
                if (block == Block::WOOD) {
                    glColor3f(0.6f, 0.4f, 0.2f);
                }
                else if (block == Block::METAL) {
                    glColor3f(0.8f, 0.8f, 0.8f);
                }
                glBegin(GL_QUADS);
                glVertex2f(static_cast<GLfloat>(x - mapGrid.getWidth() / 2), static_cast<GLfloat>(z - mapGrid.getDepth() / 2));
                glVertex2f(static_cast<GLfloat>(x + 1 - mapGrid.getWidth() / 2), static_cast<GLfloat>(z - mapGrid.getDepth() / 2));
                glVertex2f(static_cast<GLfloat>(x + 1 - mapGrid.getWidth() / 2), static_cast<GLfloat>(z + 1 - mapGrid.getDepth() / 2));
                glVertex2f(static_cast<GLfloat>(x - mapGrid.getWidth() / 2), static_cast<GLfloat>(z + 1 - mapGrid.getDepth() / 2));
                glEnd();
            }
        }
    }

    // Render grid lines
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    for (int x = 0; x <= mapGrid.getWidth(); ++x) {
        glVertex2f(static_cast<GLfloat>(x - mapGrid.getWidth() / 2), static_cast<GLfloat>(-mapGrid.getDepth() / 2));
        glVertex2f(static_cast<GLfloat>(x - mapGrid.getWidth() / 2), static_cast<GLfloat>(mapGrid.getDepth() / 2));
    }
    for (int z = 0; z <= mapGrid.getDepth(); ++z) {
        glVertex2f(static_cast<GLfloat>(-mapGrid.getWidth() / 2), static_cast<GLfloat>(z - mapGrid.getDepth() / 2));
        glVertex2f(static_cast<GLfloat>(mapGrid.getWidth() / 2), static_cast<GLfloat>(z - mapGrid.getDepth() / 2));
    }
    glEnd();

    // Render camera (global coordinates)
    float camX, camY, camZ;
    camera.getPosition(camX, camY, camZ);
    float yaw = camera.getYaw();
    float fov = 45.0f * static_cast<float>(M_PI) / 180.0f;
    float halfFov = fov / 2.0f;
    float camSize = 5.0f;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(static_cast<GLfloat>(camX - mapGrid.getWidth() / 2), static_cast<GLfloat>(camZ - mapGrid.getDepth() / 2));
    glVertex2f(static_cast<GLfloat>(camX - camSize * cos(yaw * static_cast<float>(M_PI) / 180.0f - halfFov) - mapGrid.getWidth() / 2),
        static_cast<GLfloat>(camZ - camSize * sin(yaw * static_cast<float>(M_PI) / 180.0f - halfFov) - mapGrid.getDepth() / 2));
    glVertex2f(static_cast<GLfloat>(camX - camSize * cos(yaw * static_cast<float>(M_PI) / 180.0f + halfFov) - mapGrid.getWidth() / 2),
        static_cast<GLfloat>(camZ - camSize * sin(yaw * static_cast<float>(M_PI) / 180.0f + halfFov) - mapGrid.getDepth() / 2));
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(static_cast<GLfloat>(camX - mapGrid.getWidth() / 2), static_cast<GLfloat>(camZ - mapGrid.getDepth() / 2));
    glVertex2f(static_cast<GLfloat>(camX - 20.0f * cos(yaw * static_cast<float>(M_PI) / 180.0f - halfFov) - mapGrid.getWidth() / 2),
        static_cast<GLfloat>(camZ - 20.0f * sin(yaw * static_cast<float>(M_PI) / 180.0f - halfFov) - mapGrid.getDepth() / 2));
    glVertex2f(static_cast<GLfloat>(camX - mapGrid.getWidth() / 2), static_cast<GLfloat>(camZ - mapGrid.getDepth() / 2));
    glVertex2f(static_cast<GLfloat>(camX - 20.0f * cos(yaw * static_cast<float>(M_PI) / 180.0f + halfFov) - mapGrid.getWidth() / 2),
        static_cast<GLfloat>(camZ - 20.0f * sin(yaw * static_cast<float>(M_PI) / 180.0f + halfFov) - mapGrid.getDepth() / 2));
    glEnd();

    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    renderBorder(windowWidth, windowHeight);
}