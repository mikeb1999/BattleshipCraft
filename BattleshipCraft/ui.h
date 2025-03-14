#pragma once
#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <string>

class UI {
public:
    UI();
    void renderCoordinates(int x, int y, int z) const;
    // Add more UI methods as needed (e.g., options menu rendering)
};

#endif