

#pragma once
#include "block.h"

class MapGrid {
public:
    MapGrid(int width, int height, int depth);
    ~MapGrid();
    Block::Type getBlock(int x, int y, int z) const;
    void setBlock(int x, int y, int z, Block::Type type);
    int getWidth() const { return width; }
    int getDepth() const { return depth; }

private:
    int width, height, depth;
    Block::Type* blocks; // Simplified for demonstration
};