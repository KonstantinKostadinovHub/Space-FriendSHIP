#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::init(string configFile)
{
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
    stream >> tmp >> Shield_str;

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
    Shield = Mix_LoadWAV(("music\\" + Shield_str).c_str());

    stream.close();
}

void SoundManager::play_sound(string sound)
{
    Mix_AllocateChannels(10);

    if (sound == General_Music_str)
    {
        Mix_PlayChannel(1, General, -1);
        Mix_Volume(1, 7);
    }
    else if (sound == Explosion_str)
    {
        Mix_PlayChannel(2, Explosion, 0);
        Mix_Volume(2, 13);
    }
    else if (sound == Dash_str)
    {
        Mix_PlayChannel(3, Dash, 0);
        Mix_Volume(3, 7);
    }
    else if (sound == Shooting_str)
    {
        Mix_PlayChannel(4, Shooting, 0);
        Mix_Volume(4, 6);
    }
    else if (sound == Healing_str)
    {
        Mix_PlayChannel(5, Healing, 0);
        Mix_Volume(5, 7);
    }
    else if (sound == Stop_str)
    {
        Mix_PlayChannel(6, Stop, 0);
        Mix_Volume(6, 25);
    }
    else if (sound == Reverse_str)
    {
        Mix_PlayChannel(7, Reverse, 0);
        Mix_Volume(7, 15);
    }
    else if (sound == Coin_str)
    {
        Mix_PlayChannel(8, Coin, 0);
        Mix_Volume(8, 18);
    }
    else if (sound == Shield_str)
    {
        Mix_PlayChannel(9, Shield, 0);
        Mix_Volume(9, 45);
    }
}

void SoundManager::destroyChunks()
{
    Mix_FreeChunk(General);
    General = NULL;

    Mix_FreeChunk(Explosion);
    Explosion = NULL;

    Mix_FreeChunk(Dash);
    Dash = NULL;

    Mix_FreeChunk(Shooting);
    Shooting = NULL;

    Mix_FreeChunk(Healing);
    Healing = NULL;

    Mix_FreeChunk(Stop);
    Stop = NULL;

    Mix_FreeChunk(Reverse);
    Reverse = NULL;

    Mix_FreeChunk(Coin);
    Coin = NULL;

    Mix_FreeChunk(Shield);
    Shield = NULL;

    Mix_Quit();
}
