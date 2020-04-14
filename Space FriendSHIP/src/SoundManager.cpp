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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "Mixer error: " << Mix_GetError() << endl;
    }

    General = Mix_LoadMUS(General_Music_str.c_str());
    Explosion =  Mix_LoadWAV(Explosion_str.c_str());
    Shooting =  Mix_LoadWAV(Shooting_str.c_str());
    Dash =  Mix_LoadWAV(Dash_str.c_str());
    Healing =  Mix_LoadWAV(Healing_str.c_str());
    Stop = Mix_LoadWAV(Stop_str.c_str());
    Reverse = Mix_LoadWAV(Reverse_str.c_str());

    stream.close();
}

void SoundManager::play_sound(string sound)
{
    if (sound == General_Music_str)
    {
        Mix_PlayMusic(General, -1);
    }
    else if (sound == Explosion_str)
    {
        Mix_PlayChannel(-1, Explosion, 0);
    }
    else if (sound == Dash_str)
    {
        Mix_PlayChannel(-1, Dash, 0);
    }
    else if (sound == Shooting_str)
    {
        Mix_PlayChannel(-1, Shooting, 0);
    }
    else if (sound == Healing_str)
    {
        Mix_PlayChannel(-1, Healing, 0);
    }
    else if (sound == Stop_str)
    {
        Mix_PlayChannel(-1, Stop, 0);
    }
    else if (sound == Reverse_str)
    {
        Mix_PlayChannel(-1, Reverse, 0);
    }
}

void SoundManager::destroy()
{
    Mix_FreeMusic(General);
    General = NULL;

    Mix_FreeChunk(Explosion);
    Explosion = NULL;

    Mix_FreeChunk(Shooting);
    Shooting = NULL;

    Mix_FreeChunk(Dash);
    Dash = NULL;

    Mix_FreeChunk(Healing);
    Healing = NULL;

    Mix_Quit();
}
