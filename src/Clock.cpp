#include "Clock.hpp"

Clock::Clock(const char* path, int posx, int posy, float scale, SDL_Renderer *r)
{
    text.Init(path, posx, posy, scale, r);
}

Clock::~Clock()
{
}

void Clock::Refresh()
{
    timer.Update();
}

void Clock::SetTime(unsigned int ptime)
{
    time = ptime;
    orgTime = ptime;
}

void Clock::Reset()
{
    color = {0xff, 0xff, 0xff};
    time = orgTime;
}

bool Clock::NoTime()
{
    if(time == 0)
        return true;
    return false;
}

void Clock::Update(SDL_Renderer *r)
{
    if(timer.GetDeltaTime() >= 1.0f/1)
    {
        if(time == 0) 
        {
            color.r = 0x00;
            text.SetColor(&color);
            text.Update((char*)std::to_string(time).c_str(), r, false);
        }
        // std::cout << timer.GetDeltaTime() << std::endl;
        timer.Reset();
        if(time != 0)
        {
            // modify the color of a timer Text
            color.b -= 0xff/orgTime;
            color.g -= 0xff/orgTime;
            text.SetColor(&color);
            text.Update((char*)std::to_string(time).c_str(), r, false); 
            time--;
        }
        return;
    }
}

void Clock::Render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, text.GetTexture(), nullptr, &text.rect);
}
