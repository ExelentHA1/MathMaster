#include "Timer.hpp"

Timer::Timer()
{
    Reset();
    timeScale = 1.f;
}

Timer::~Timer()
{
}

void Timer::Reset()
{
    startTicks = SDL_GetTicks64();
    elapseTicks = 0;
    deltaTime = 0.0f;
}

float Timer::GetDeltaTime()
{
    return deltaTime;
}

void Timer::SetTimeScale(float t)
{
    timeScale = t;
}

float Timer::GetTimeScale()
{
    return timeScale;
}

void Timer::Update()
{
    elapseTicks = SDL_GetTicks64() - startTicks;
    deltaTime = elapseTicks * 0.001f;
}
