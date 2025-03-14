

#pragma once
#include <SDL.h>
#include <memory>
#include <string>
#include "scene.h"
#include "renderer.h"
#include "camera.h"
#include "coordinate_system.h"
#include "minimap.h"
#include "MapGrid.h"

class Game {
public:
    Game();
    ~Game();

    bool initialize();
    void run();
    void toggleFullscreen();
    void logMessage(const std::string& message);
    void placeBlock();
    void resetCamera();

private:
    SDL_Window* window;
    Renderer* renderer;
    Scene scene;
    Camera camera;
    CoordinateSystem coordSystem;
    MiniMap minimap;
    MapGrid mapGrid;
    bool running;
    bool isFullscreen;
    int lastMouseX, lastMouseY;
    bool isRotating;
    float lastDeltaX, lastDeltaY;
    float zoomLevel; // For camera zoom control
};