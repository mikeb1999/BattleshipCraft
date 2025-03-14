#pragma once
#include <vector>
class Ship {
public:
    std::vector<Block> blocks;

    bool canPlaceBlock(int x, float y, int z) {
        for (const auto& block : blocks) {
            if (block.x == x && block.y == y && block.z == z) {
                return false; // Position occupied
            }
        }
        return true;
    }

    void addBlock(int x, float y, int z, Block::Type type) {
        blocks.push_back({ x, y, z, type });
    }
};

struct Block {
    int x;
    float y;
    int z;
    Block::Type type;
};