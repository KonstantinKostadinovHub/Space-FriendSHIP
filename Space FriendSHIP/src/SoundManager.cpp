#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::init(string configFile)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    m_configFile = "config\\" + configFile;
    fstream stream;

    stream.open(m_configFile.c_str());
    stream >> tmp >> General_Music_str;
    stream >> tmp >> Explosion_str;
    stream >> tmp >> Shooting_str;
    stream >> tmp >> Dash_str;
    stream >> tmp >> Healing_str;
    stream >> tmp >> Stop_str;
    stream >> tmp >> Reverse_str;
    stream >> tmp >> Coin_str;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "Mixer error: " << Mix_GetError() << endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }

    General = Mix_LoadWAV(("music\\" + General_Music_str).c_str());
    Explosion =  Mix_LoadWAV(("music\\" + Explosion_str).c_str());
    Shooting =  Mix_LoadWAV(("music\\" + Shooting_str).c_str());
    Dash =  Mix_LoadWAV(("music\\" + Dash_str).c_str());
    Healing =  Mix_LoadWAV(("music\\" + Healing_str).c_str());
    Stop = Mix_LoadWAV(("music\\" + Stop_str).c_str());
    Reverse = Mix_LoadWAV(("music\\" + Reverse_str).c_str());
    Coin = Mix_LoadWAV(("music\\" + Coin_str).c_str());

    stream.close();
}

void SoundManager::play_sound(string sound)
{
    Mix_AllocateChannels(16);

    if (sound == General_Music_str)
    {
        Mix_PlayChannel(7, General, -1);
        Mix_Volume(7, 10);
    }
    else if (sound == Explosion_str)
    {
        Mix_PlayChannel(1, Explosion, 0);
        Mix_Volume(1, 15);
    }
    else if (sound == Dash_str)
    {
        Mix_PlayChannel(2, Dash, 0);
        Mix_Volume(2, 7);
    }
    else if (sound == Shooting_str)
    {
        Mix_PlayChannel(3, Shooting, 0);
        Mix_Volume(3, 7);
    }
    else if (sound == Healing_str)
    {
        Mix_PlayChannel(4, Healing, 0);
        Mix_Volume(4, 7);
    }
    else if (sound == Stop_str)
    {
        Mix_PlayChannel(5, Stop, 0);
        Mix_Volume(5, 7);
    }
    else if (sound == Reverse_str)
    {
        Mix_PlayChannel(6, Reverse, 0);
        Mix_Volume(6, 7);
    }
    else if (sound == Coin_str)
    {
        Mix_PlayChannel(8, Coin, 0);
        Mix_Volume(8, 18);
    }
}

void SoundManager::destroy()
{
    Mix_FreeChunk(General);
    General = NULL;

    Mix_FreeChunk(Explosion);
    Explosion = NULL;

    Mix_FreeChunk(Shooting);
    Shooting = NULL;

    Mix_FreeChunk(Dash);
    Dash = NULL;

    Mix_FreeChunk(Healing);
    Healing = NULL;

    Mix_FreeChunk(Stop);
    Stop = NULL;

    Mix_FreeChunk(Reverse);
    Reverse = NULL;

    Mix_FreeChunk(Coin);
    Coin = NULL;

    Mix_Quit();
}
