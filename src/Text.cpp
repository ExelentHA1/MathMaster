#include "Text.hpp"

Text::Text()
{
}

Text::~Text()
{
}

void Text::Init(const char *path, int posx, int posy, float pscale, SDL_Renderer *r)
{
    if(TTF_Init() == -1)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    }
    font= TTF_OpenFont(path, 256);
    if(font == nullptr)
    {
        std::cerr << "Failed to load fonts Error: " << TTF_GetError() << std::endl;
    }
    color = {
        0xff, // r
        0xff, // b
        0xff, // g
        0xff // a
    };
    surface = TTF_RenderText_Solid(font, " ", color);
    if (surface == nullptr) 
    {
        std::cerr << "INIT Failed to create surface. Error: " << TTF_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(r, surface);
    if (texture == nullptr) 
    {
        std::cerr << "INIT Failed to create texture from surface. Error: " << SDL_GetError() << std::endl;
    }

    x = posx;
    y = posy;
    scale = pscale;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    offx = w / 2 * -1;
    offy = h / 2 * -1;
    rect.x = x + offx * scale;
    rect.y = y + offy * scale;
    rect.w = w * scale;
    rect.h = h * scale;
}

void Text::Update(const char *ptext, SDL_Renderer *renderer, bool forceUpdate)
{
    // check if the text has changed
    if (strcmp(ptext, prevText.c_str()) != 0 || forceUpdate) 
    {
        // update the previous text and color
        prevText = ptext;
        if (surface)
            SDL_FreeSurface(surface);
        surface = TTF_RenderText_Solid(font, ptext, color);
        if (surface == nullptr) 
        {
            std::cerr << "UPDATE Failed to create surface. Error: " << TTF_GetError() << std::endl;
        }
        if (texture)
            SDL_DestroyTexture(texture);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) 
        {
            std::cerr << "UPDATE Failed to create texture from surface. Error: " << SDL_GetError() << std::endl;
        }
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        offx = w / 2 * -1;
        offy = h / 2 * -1;
        rect.x = x + offx * scale;
        rect.y = y + offy * scale;
        rect.w = w * scale;
        rect.h = h * scale;
    }
}

void Text::SetColor(SDL_Color *pcolor)
{
    color = {0,0,0,0};
    color = *pcolor;
}

SDL_Color Text::GetColor()
{
    return color;
}

SDL_Texture *Text::GetTexture()
{
    return texture;
}
