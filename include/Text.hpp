#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text
{
public:
    Text();
    ~Text();
    void Init(const char *path, int posx, int posy, float pscale, SDL_Renderer *r);
    void Update(const char *text, SDL_Renderer *renderer, bool forceUpdate);
    // void Render(SDL_Renderer *renderer);
    void SetColor(SDL_Color *pcolor);
    SDL_Color GetColor();
    SDL_Texture* GetTexture();
    SDL_Rect rect;
private:
    std::string prevText = "";
    SDL_Color color, prevColor;
    TTF_Font *font;
    SDL_Surface *surface;
    SDL_Texture *texture;

    float scale; // scale of an texture
    int offx, offy; // offset
    int w,h; // to properly calibrate the offset
    int x,y; // positions
};