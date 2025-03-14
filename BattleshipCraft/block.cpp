

#include "block.h"

Block::Block(float x, float y, float z, Type type)
    : x(static_cast<int>(x)), y(static_cast<int>(y)), z(static_cast<int>(z)), type(type) {
}

void Block::setPosition(float x, float y, float z) {
    this->x = static_cast<int>(x);
    this->y = static_cast<int>(y);
    this->z = static_cast<int>(z);
}

float Block::getWeight() const {
    switch (type) {
    case WOOD: return 0.8f;  // Wood is lighter
    case METAL: return 2.0f; // Metal is heavier
    default: return 1.0f;    // Default weight for AIR or DEFAULT
    }
}

float Block::getBuoyancy() const {
    switch (type) {
    case WOOD: return 1.2f;  // Wood floats well
    case METAL: return 0.1f; // Metal barely floats
    default: return 0.0f;    // AIR or DEFAULT has no buoyancy
    }
}