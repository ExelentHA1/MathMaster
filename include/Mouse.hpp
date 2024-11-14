#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Mouse
{
public:
    Mouse(SDL_Renderer *renderer, const char *path);
    ~Mouse();

    void update(); // updates positions
    SDL_Texture *GetTexture();
    void Draw(SDL_Renderer *r);
    SDL_Rect point; // use to inteact with button
private:
    SDL_Texture *texture;
    SDL_Rect dest; 
};