

#pragma once

class Block {
public:
    enum Type {
        AIR,
        WOOD,
        METAL,
        DEFAULT
    };

    Block(float x = 0.0f, float y = 0.0f, float z = 0.0f, Type type = AIR);
    void setPosition(float x, float y, float z);
    float getWeight() const;
    float getBuoyancy() const;

private:
    int x, y, z; // Block position in the grid (integer coordinates)
    Type type;
};