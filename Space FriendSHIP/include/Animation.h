#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <fstream>
#include <ctime>

#include "Engine.h"

class Animation
{
public:
    coordinates m_coor;
    coordinates m_direction;

    SDL_Rect m_objectRect;
    SDL_Rect m_SpriteRect;
    SDL_Rect m_Animation;
    SDL_Texture* m_objectTexture;

    SDL_Point m_center;
    string m_img;
    string m_configFile;

    float m_actionEffect;
    float m_rotationAngle;

    int m_health = 2;
    int m_frameCounter;
    int m_FrameCount;

    time_t m_startCounter;
    time_t m_FrameCooldown;

    bool finished = false;

    Animation();

    virtual ~Animation();
    virtual void init(string configFile, coordinates coor,SDL_Renderer* renderer,float rotation,SDL_Point* center);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
};

#endif
