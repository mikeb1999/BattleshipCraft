

#include "physics.h"
#include <iostream>

Physics::Physics() {}

float Physics::calculateBuoyancy(float blockWeight, float buoyancyFactor) const {
    float volume = 1.0f;
    float buoyantForce = volume * waterDensity * gravity * buoyancyFactor;
    return buoyantForce;
}

float Physics::updatePosition(float currentY, float weight, float buoyancy, float deltaTime) {
    float netForce = calculateBuoyancy(weight, buoyancy) - (weight * gravity);
    float acceleration = (weight > 0) ? (netForce / weight) : 0.0f;
    float velocity = acceleration * deltaTime * 5.0f;
    velocity *= 0.9f;
    float newY = currentY + velocity;
    if (newY < 0.0f) newY = 0.0f;
    if (newY > 9.0f) newY = 9.0f;
    std::cout << "Physics: currentY=" << currentY << ", netForce=" << netForce << ", velocity=" << velocity << ", newY=" << newY << std::endl;
    return newY;
}