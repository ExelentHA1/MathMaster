#pragma once

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>

#include "Text.hpp"
#include "Timer.hpp"
#include "Button.hpp"
#include "Sound.hpp"

class TextBox : public Button
{
public:
    TextBox(const char *path,int posx, int posy, float pscale, SDL_Renderer *r, bool interactive);
    ~TextBox();

    void LoadSound(const char *path);

    void Refresh();
    void SetRenderSpeed(float seconds);
    void RenderDynamic(SDL_Renderer *renderer); // set the text dinamically on the screen
    void Update(SDL_Renderer *r);
    void RenderStatic(SDL_Renderer *renderer);
    void SetText(std::string ptext);
    void Enable(bool set);
private:
    std::unique_ptr<Timer> timer = std::make_unique<Timer>(); // std::unique_ptr<typename T> deletes the objest automatically
    
    Sound s;
    Text text;
    std::string t, orgT;
    SDL_Color color {0xcc, 0xda, 0xd7, 200};
    int x, y, offx, offy, index;
    float scale, seconds;
    bool isButton, isEnable;
};