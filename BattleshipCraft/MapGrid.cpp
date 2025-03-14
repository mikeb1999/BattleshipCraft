

#include "MapGrid.h"
#include <cstring>

MapGrid::MapGrid(int width, int height, int depth)
    : width(width), height(height), depth(depth) {
    blocks = new Block::Type[width * height * depth];
    std::memset(blocks, Block::AIR, width * height * depth * sizeof(Block::Type));
}

MapGrid::~MapGrid() {
    delete[] blocks;
}

Block::Type MapGrid::getBlock(int x, int y, int z) const {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
        return Block::AIR;
    }
    return blocks[(y * depth + z) * width + x];
}

void MapGrid::setBlock(int x, int y, int z, Block::Type type) {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
        return;
    }
    blocks[(y * depth + z) * width + x] = type;
}