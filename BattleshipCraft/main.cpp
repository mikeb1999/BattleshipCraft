

#include "game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Game game;
    if (!game.initialize()) {
        std::cerr << "Failed to initialize game. Exiting..." << std::endl;
        return -1;
    }

    std::cout << "Game initialized successfully. Starting main loop..." << std::endl;
    game.run();

    std::cout << "Game terminated gracefully." << std::endl;
    return 0;
}