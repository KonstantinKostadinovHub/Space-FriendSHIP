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
    string m_configFile;
    string m_img;
    SDL_Texture* m_objectTexture;
    struct coordinates m_coor;
    struct coordinates m_direction;
    float m_speed;
    int m_health;
    int m_collisonDamage;
    float m_rotationAngle;

    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
    virtual void init(string configFile, struct coordinates coor, struct coordinates direction);
protected:

private:
};

#endif // PROJECTILE_H
