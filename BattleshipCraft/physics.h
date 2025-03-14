

#ifndef PHYSICS_H
#define PHYSICS_H

class Physics {
public:
    Physics();
    float calculateBuoyancy(float blockWeight, float buoyancyFactor) const;
    float updatePosition(float currentY, float weight, float buoyancy, float deltaTime);
    const float waterDensity = 1.0f;
    const float gravity = 9.81f;
};

#endif