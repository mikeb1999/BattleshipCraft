

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <vector>
#include "block.h"

struct BlockPosition {
    int x = 0;
    float y = 0.0f;
    int z = 0;
    Block::Type type = Block::Type::WOOD;
    float velocityY = 0.0f;
};

class Battleship {
public:
    Battleship();
    void addBlock(int x, float y, int z, Block::Type type);
    void updateBlockPosition(int x, int y, int z, float newY);
    void updatePhysics(float deltaTime);
    std::vector<BlockPosition> getBlocks() const;
    void printInfo() const;
    bool canPlaceBlock(int x, float y, int z) const;

private:
    std::vector<BlockPosition> blocks;
};

#endif