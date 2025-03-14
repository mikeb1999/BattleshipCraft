

#include "coordinate_system.h"
#include <GL/glew.h>
#include <SDL.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void CoordinateSystem::globalToLocal(const Camera& camera, float globalX, float globalY, float globalZ,
    float& localX, float& localY, float& localZ) {
    float camX, camY, camZ;
    camera.getPosition(camX, camY, camZ);

    float dx = globalX - camX;
    float dy = globalY - camY;
    float dz = globalZ - camZ;

    float yawRad = static_cast<float>(camera.getYaw() * M_PI / 180.0);

    localX = static_cast<float>(cos(yawRad) * dx + sin(yawRad) * dz);
    localY = dy;
    localZ = static_cast<float>(-sin(yawRad) * dx + cos(yawRad) * dz);
}

void CoordinateSystem::localToGlobal(const Camera& camera, float localX, float localY, float localZ,
    float& globalX, float& globalY, float& globalZ) {
    float camX, camY, camZ;
    camera.getPosition(camX, camY, camZ);

    float yawRad = static_cast<float>(camera.getYaw() * M_PI / 180.0);

    globalX = static_cast<float>(camX + cos(yawRad) * localX - sin(yawRad) * localZ);
    globalY = camY + localY;
    globalZ = static_cast<float>(camZ + sin(yawRad) * localX + cos(yawRad) * localZ);
}