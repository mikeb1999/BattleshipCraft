

#include "renderer.h"
#include <GL/glew.h> // Correct include order
#include <SDL.h>
#include <iostream>

Renderer::Renderer(SDL_Window* window) : window(window) {}

Renderer::~Renderer() {
    SDL_GL_DeleteContext(glContext);
}

bool Renderer::initialize(int width, int height) {
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
        return false;
    }

    GLenum glewResult = glewInit();
    if (glewResult != GLEW_OK) {
        std::cerr << "GLEW initialization failed: " << glewGetErrorString(glewResult) << std::endl;
        return false;
    }

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return true;
}

void Renderer::beginRender(const Camera& camera) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}

void Renderer::render(const Scene& scene) {
    scene.render();
}

void Renderer::endRender() {
    SDL_GL_SwapWindow(window);
}

void Renderer::updateViewport(int width, int height) {
    glViewport(0, 0, width, height);
}