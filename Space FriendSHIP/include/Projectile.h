#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <SDL2/SDL.h>
#include "Engine.h"

class Projectile
{
public:
    Projectile();
    virtual ~Projectile();

    SDL_Rect m_objectRect;
    SDL_Texture* m_objectTexture;

    string m_configFile;
    string m_img;

    struct coordinates m_coor;
    struct coordinates m_direction;

    float m_speed;
    float m_rotationAngle;

    int m_health;
    int m_collisonDamage;

    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
    virtual void init(string configFile, coordinates coor, float rotation, Projectile* projectile);
    virtual void load(string configFile, SDL_Renderer* renderer);

};

#endif
