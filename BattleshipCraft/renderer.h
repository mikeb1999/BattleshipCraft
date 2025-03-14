

#pragma once
#include <SDL.h>
#include "camera.h"
#include "scene.h" // Added to declare the Scene class

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();
    bool initialize(int width, int height);
    void beginRender(const Camera& camera);
    void render(const Scene& scene); // Ensure Scene is recognized
    void endRender();
    void updateViewport(int width, int height);

private:
    SDL_Window* window;
    SDL_GLContext glContext;
};