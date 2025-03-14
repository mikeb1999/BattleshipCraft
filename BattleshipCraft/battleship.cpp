

#include "battleship.h"
#include <iostream>
#include <cmath> // For std::abs

Battleship::Battleship() {}

void Battleship::addBlock(int x, float y, int z, Block::Type type) {
    BlockPosition block;
    block.x = x;
    block.y = std::round(y); // Snap to nearest integer to align with grid
    block.z = z;
    block.type = type;
    block.velocityY = 0.0f;
    blocks.push_back(block);
    std::cout << "Added block at (" << x << ", " << block.y << ", " << z << ") with type " << static_cast<int>(type) << std::endl;
}

void Battleship::updateBlockPosition(int x, int y, int z, float newY) {
    for (auto& block : blocks) {
        // Use a small tolerance for y comparison due to floating-point precision
        if (block.x == x && std::abs(block.y - static_cast<float>(y)) < 0.01f && block.z == z) {
            block.y = newY;
            std::cout << "Updated block at (" << x << ", " << y << ", " << z << ") to y=" << newY << std::endl;
            return;
        }
    }
    std::cout << "No block found at (" << x << ", " << y << ", " << z << ") to update\n";
}

void Battleship::updatePhysics(float deltaTime) {
    const float waterLevel = 5.0f;
    for (auto& block : blocks) {
        if (block.type == Block::Type::WOOD) {
            if (block.y < waterLevel) {
                block.velocityY += 0.1f * deltaTime; // Buoyancy force
                if (block.velocityY > 0.5f) block.velocityY = 0.5f;
                std::cout << "Wood block at (" << block.x << ", " << block.y << ", " << block.z << ") floating: velocityY=" << block.velocityY << "\n";
            }
            else {
                block.velocityY = 0.0f;
                block.y = waterLevel;
                std::cout << "Wood block at (" << block.x << ", " << block.y << ", " << block.z << ") at water level\n";
            }
        }
        else if (block.type == Block::Type::METAL) {
            block.velocityY -= 0.2f * deltaTime; // Gravity force
            if (block.velocityY < -1.0f) block.velocityY = -1.0f;
            std::cout << "Metal block at (" << block.x << ", " << block.y << ", " << block.z << ") sinking: velocityY=" << block.velocityY << "\n";
        }

        block.y += block.velocityY * deltaTime;

        if (block.y < 0.0f) {
            block.y = 0.0f;
            block.velocityY = 0.0f;
            std::cout << "Block at (" << block.x << ", " << block.y << ", " << block.z << ") hit bottom (y=0)\n";
        }
        else if (block.y > 10.0f) {
            block.y = 10.0f;
            block.velocityY = 0.0f;
            std::cout << "Block at (" << block.x << ", " << block.y << ", " << block.z << ") hit top (y=10)\n";
        }
    }
}

std::vector<BlockPosition> Battleship::getBlocks() const {
    return blocks;
}

void Battleship::printInfo() const {
    std::cout << "Battleship block grid status: " << blocks.size() << " blocks" << std::endl;
    for (const auto& block : blocks) {
        std::cout << "Block at (" << block.x << ", " << block.y << ", " << block.z << ") type " << static_cast<int>(block.type) << std::endl;
    }
}

bool Battleship::canPlaceBlock(int x, float y, int z) const {
    for (const auto& block : blocks) {
        // Use a small tolerance for floating-point comparison
        if (static_cast<int>(block.x) == x &&
            static_cast<int>(std::round(block.y)) == static_cast<int>(std::round(y)) &&
            static_cast<int>(block.z) == z) {
            return false; // Position is occupied
        }
    }
    return x >= 0 && x <= 9 && y >= 0 && y <= 9 && z >= 0 && z <= 9; // Within grid bounds
}
