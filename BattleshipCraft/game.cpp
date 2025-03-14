

#include <windows.h>
#include <GL/gl.h>
#include <GL/glew.h>
#include <SDL.h>
#include <GL/glu.h>
#include "game.h"
#include "config.h"
#include "coordinate_system.h"
#include "Camera.h"
#include "Ground.h"  // Added
#include "Skybox.h"  // Added
#include "Grid3D.h"  // Added
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // Added

Game::Game()
    : window(nullptr), renderer(nullptr), running(false), isFullscreen(false),
    lastMouseX(0), lastMouseY(0), isRotating(false), lastDeltaX(0.0f), lastDeltaY(0.0f),
    minimap(200, 200, static_cast<int>(Config::GROUND_SIZE * 2)),
    mapGrid(static_cast<int>(Config::GROUND_SIZE * 2), 10, static_cast<int>(Config::GROUND_SIZE * 2)),
    zoomLevel(10.0f)
{
    scene.addObject(std::make_unique<Ground>());
    scene.addObject(std::make_unique<Skybox>());
    scene.addObject(std::make_unique<Grid3D>());
}

Game::~Game() {
    if (renderer) delete renderer;
    if (window) {
        SDL_GL_DeleteContext(SDL_GL_GetCurrentContext()); // Clean up OpenGL context
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("BattleshipCraft", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        return false;
    }

    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK) {
        std::cerr << "GLEW initialization failed: " << glewGetErrorString(glewErr) << std::endl;
        return false;
    }
    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

    renderer = new Renderer(window);
    if (!renderer->initialize(800, 600)) {
        std::cerr << "Renderer initialization failed." << std::endl;
        return false;
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPosition[] = { 0.0f, 20.0f, 0.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    running = true;
    return true;
}

void Game::resetCamera() {
    camera = Camera();
    zoomLevel = 10.0f;
}

void Game::toggleFullscreen() {
    isFullscreen = !isFullscreen;
    if (isFullscreen) {
        if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
            std::cerr << "Failed to switch to fullscreen mode: " << SDL_GetError() << std::endl;
            isFullscreen = false;
            logMessage("Failed to switch to fullscreen mode: " + std::string(SDL_GetError()));
        }
        else {
            int width, height;
            SDL_GetWindowSize(window, &width, &height);
            logMessage("Switched to fullscreen mode at " + std::to_string(width) + "x" + std::to_string(height));
            renderer->updateViewport(width, height);
        }
    }
    else {
        if (SDL_SetWindowFullscreen(window, 0) != 0) {
            std::cerr << "Failed to switch to windowed mode: " << SDL_GetError() << std::endl;
            isFullscreen = true;
            logMessage("Failed to switch to windowed mode: " + std::string(SDL_GetError()));
        }
        else {
            SDL_SetWindowSize(window, 800, 600);
            SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            logMessage("Switched to windowed mode at 800x600");
            renderer->updateViewport(800, 600);
        }
    }
}

void Game::placeBlock() {
    float camX, camY, camZ;
    camera.getPosition(camX, camY, camZ);
    int x = static_cast<int>(camX + 0.5f);
    int z = static_cast<int>(camZ + 0.5f);
    if (mapGrid.getBlock(x, 0, z) == Block::AIR) {
        mapGrid.setBlock(x, 0, z, Block::WOOD);
        logMessage("Placed block at global (" + std::to_string(x) + ", 0, " + std::to_string(z) + ")");
    }
}

void Game::run() {
    resetCamera();
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEMOTION) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (isRotating) {
                    int deltaX = x - lastMouseX;
                    int deltaY = y - lastMouseY;
                    float rotationSpeed = 60.0f * deltaTime;
                    camera.rotate(static_cast<float>(deltaX * rotationSpeed), static_cast<float>(deltaY * rotationSpeed));
                    lastMouseX = x;
                    lastMouseY = y;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_MIDDLE) {
                    isRotating = true;
                    SDL_GetMouseState(&lastMouseX, &lastMouseY);
                }
                else if (event.button.button == SDL_BUTTON_LEFT) {
                    placeBlock();
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_MIDDLE) {
                    isRotating = false;
                }
            }
            else if (event.type == SDL_MOUSEWHEEL) {
                zoomLevel += event.wheel.y * 1.0f;
                zoomLevel = std::max(1.0f, std::min(50.0f, zoomLevel));
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_f: toggleFullscreen(); break;
                case SDLK_r: resetCamera(); break;
                case SDLK_ESCAPE: running = false; break;
                }
            }
        }

        const Uint8* state = SDL_GetKeyboardState(nullptr);
        float moveSpeed = 10.0f * deltaTime;
        float deltaForward = 0.0f, deltaRight = 0.0f, deltaUp = 0.0f;
        if (state[SDL_SCANCODE_W]) deltaForward += moveSpeed;
        if (state[SDL_SCANCODE_S]) deltaForward -= moveSpeed;
        if (state[SDL_SCANCODE_A]) deltaRight -= moveSpeed;
        if (state[SDL_SCANCODE_D]) deltaRight += moveSpeed;
        if (state[SDL_SCANCODE_Q]) deltaUp -= moveSpeed;
        if (state[SDL_SCANCODE_E]) deltaUp += moveSpeed;
        camera.move(deltaForward, deltaRight, deltaUp);

        float camX, camY, camZ;
        camera.getPosition(camX, camY, camZ);
        camY = std::max(1.0f, camY);
        camera.setPosition(camX, camY, camZ); // Update camera position

        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        glViewport(0, 0, windowWidth, windowHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, static_cast<float>(windowWidth) / windowHeight, 0.1f, 2000.0f);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer->beginRender(camera);
        camera.applyViewMatrix();
        renderer->render(scene);

        GLenum err = glGetError();
        if (err != GL_NO_ERROR) std::cerr << "OpenGL error after main scene: " << err << std::endl;

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        minimap.render(mapGrid, camera, scene, windowWidth, windowHeight);
        glPopMatrix();

        err = glGetError();
        if (err != GL_NO_ERROR) std::cerr << "OpenGL error after minimap: " << err << std::endl;

        renderer->endRender();

        SDL_Delay(16); // ~60 FPS
    }
}

void Game::logMessage(const std::string& message) {
    std::ofstream logFile("battleship_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    }
    std::cout << message << std::endl;
}