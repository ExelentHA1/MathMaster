#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Timer
{
public:
    Timer();
    ~Timer();

    void Reset();
    float GetDeltaTime();

    void SetTimeScale(float t);
    float GetTimeScale();
    
    void Update();
private:
    unsigned int startTicks, elapseTicks;
    float deltaTime, timeScale;
};