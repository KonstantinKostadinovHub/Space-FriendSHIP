#ifndef DEFINES_H
#define DEFINES_H

#include <SDL2/SDL.h>
#include <cmath>

enum GAME_STATE
{
    NOSCENE = 0,
    MENU = 1,
    GAME_SINGLEPLAYER = 2,
    GAME_MULTIPLAYER = 3,
    SHOP = 4,
    DIED = 5
};

#endif // DEFINES_H
