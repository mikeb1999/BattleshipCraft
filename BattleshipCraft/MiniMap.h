

#pragma once
#include <GL/glew.h>
#include "MapGrid.h" // Changed from map_grid.h to MapGrid.h
#include "camera.h"
#include "scene.h"

class MiniMap {
public:
    MiniMap(int width, int height, int mapSize);
    void render(const MapGrid& mapGrid, const Camera& camera, const Scene& scene, int windowWidth, int windowHeight);

private:
    int width, height, mapSize;
    void renderBorder(int windowWidth, int windowHeight);
};