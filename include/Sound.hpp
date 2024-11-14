#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound
{
public:
    Sound();
    ~Sound();
    
    void Init(const char *path);
    bool Check();
    // can add pause functionality
    void Stop();
    void Play();
    void Close();
private:
    Mix_Music *sound;
    bool hasSound;
};

