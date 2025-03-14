

#include "camera.h"
#include <GL/glew.h>
#include <SDL.h>
#include <GL/glu.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Camera::Camera() :
    posX(0.0f), posY(5.0f), posZ(10.0f),
    yaw(0.0f), pitch(-45.0f)
{
    updateDirectionVectors();
}

void Camera::move(float forward, float right, float up) {
    posX += forward * forwardX + right * rightX + up * upX;
    posY += forward * forwardY + right * rightY + up * upY;
    posZ += forward * forwardZ + right * rightZ + up * upZ;
}

void Camera::rotate(float yawDelta, float pitchDelta) {
    yaw += yawDelta;
    pitch += pitchDelta;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateDirectionVectors();
}

void Camera::updateDirectionVectors() {
    float yawRad = static_cast<float>(yaw * M_PI / 180.0);
    float pitchRad = static_cast<float>(pitch * M_PI / 180.0);

    forwardX = static_cast<float>(cos(pitchRad) * sin(yawRad));
    forwardY = static_cast<float>(sin(pitchRad));
    forwardZ = static_cast<float>(cos(pitchRad) * cos(yawRad));

    rightX = static_cast<float>(sin(yawRad - M_PI / 2.0));
    rightY = 0.0f;
    rightZ = static_cast<float>(cos(yawRad - M_PI / 2.0));

    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
}

void Camera::applyViewMatrix() const {
    gluLookAt(
        posX, posY, posZ,
        posX + forwardX, posY + forwardY, posZ + forwardZ,
        upX, upY, upZ
    );
}

void Camera::getPosition(float& x, float& y, float& z) const {
    x = posX;
    y = posY;
    z = posZ;
}

void Camera::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

float Camera::getYaw() const { return yaw; }
float Camera::getPitch() const { return pitch; }