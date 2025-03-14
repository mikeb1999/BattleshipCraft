

#include "input.h"

Input::Input() {}

bool Input::isMouseClicked(SDL_Event& event, int& x, int& y) {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        x = event.button.x;
        y = event.button.y;
        return true;
    }
    return false;
}