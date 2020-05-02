#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class SoundManager
{
public:
    SoundManager();
    virtual ~SoundManager();

    void init(string configFile);
    void destroy();
    void play_sound(string sound);

    string m_configFile;
    string tmp;

    string General_Music_str;
    string Shooting_str;
    string Dash_str;
    string Explosion_str;
    string Healing_str;
    string Stop_str;
    string Reverse_str;
    string Coin_str;
    string Shield_str;

    Mix_Chunk* General;
    Mix_Chunk* Explosion;
    Mix_Chunk* Shooting;
    Mix_Chunk* Dash;
    Mix_Chunk* Healing;
    Mix_Chunk* Stop;
    Mix_Chunk* Reverse;
    Mix_Chunk* Coin;
    Mix_Chunk* Shield;

protected:

private:
};

#endif
