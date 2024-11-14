#include "Sound.hpp"

Sound::Sound()
: sound(nullptr)
{
    hasSound = false;
}

Sound::~Sound()
{
    Close();
}

void Sound::Init(const char *path)
{
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096))
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
    sound = Mix_LoadMUS(path);
    if(sound == nullptr)
    {
        std::cerr << "failed to load the music. Error: " << Mix_GetError() << std::endl;
    }
    else
    {
        hasSound = true;
    }
}

bool Sound::Check()
{
    return hasSound;
}

void Sound::Stop()
{
    Mix_HaltMusic();
}

void Sound::Play()
{
    Mix_PlayMusic(sound, 0);
}



void Sound::Close()
{
    Mix_FreeMusic(sound);
    Mix_CloseAudio();
}
