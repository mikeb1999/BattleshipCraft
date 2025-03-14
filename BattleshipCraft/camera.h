

#pragma once
#include <GL/glu.h>

class Camera {
public:
    Camera();
    void move(float forward, float right, float up);
    void rotate(float yawDelta, float pitchDelta);
    void applyViewMatrix() const;
    void getPosition(float& x, float& y, float& z) const;
    void setPosition(float x, float y, float z); // Added setter
    float getYaw() const;
    float getPitch() const;

private:
    float posX, posY, posZ;
    float yaw, pitch;
    float forwardX, forwardY, forwardZ;
    float rightX, rightY, rightZ;
    float upX, upY, upZ;
    void updateDirectionVectors();
};