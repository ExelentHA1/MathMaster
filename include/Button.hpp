#pragma once

#include <iostream>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Mouse.hpp"

class Button
{
public:
    Button();
    ~Button();
    // automatically set thier sizes according to the screen
    void Events(const SDL_Event *ev); // mouse handle events
    bool Clicked();
protected:
    bool pressed = false;
    bool hovered = false;
    SDL_Rect *rect; // size and bounderies
};