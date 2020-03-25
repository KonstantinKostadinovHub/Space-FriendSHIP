#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>

#include <Engine.h>
#include <Gun.h>

using namespace std;

class Enemy
{
public:
    Enemy();
    virtual ~Enemy();

    string m_configFile;
    string m_img;
    string m_bulletName;
    string tmp;

    int m_health;
    int m_collisonDamage;
    int m_pointsGiven;

    float m_attackSpeed;
    float m_speed;
    float m_rotationAngle;

    SDL_Point m_center;

    SDL_Rect m_objectRect;
    SDL_Texture* m_objectTexture;

    struct coordinates m_coor;
    struct coordinates m_direction;

    vector <Gun*> m_guns;

    virtual void init(string configFile, coordinates coor, float rotation, SDL_Renderer* renderer);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
    virtual void dealDamage(int damage);
    virtual void action();

protected:

private:
};

#endif // ENEMY_H

