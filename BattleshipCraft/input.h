

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input {
public:
    Input();
    bool isMouseClicked(SDL_Event& event, int& x, int& y);
};

#endif