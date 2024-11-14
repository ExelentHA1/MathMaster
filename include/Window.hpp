#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

struct WindowRenderer
{
    WindowRenderer();
    ~WindowRenderer();
    
    void create(const char* title, int Width, int Height);
    void loadImage(const char *path);
    void clean();
    void clear();
    void present();
    void render(SDL_Texture *t,int posx, int posy, int offsetx, int offsety, int size);
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Window *window;
};


