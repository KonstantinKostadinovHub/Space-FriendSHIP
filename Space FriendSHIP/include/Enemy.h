#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include<SDL2/SDL.h>

#include <Engine.h>
#include <Gun.h>

using namespace std;

class Enemy
{
public:
    Enemy();
    virtual ~Enemy();

    string m_configFile;
    int m_health;
    int m_collisonDamage;
    float m_attackSpeed;
    float m_speed;

    string m_img;
    SDL_Rect m_objectRect;
    struct coordinates m_coor;
    struct coordinates m_direction;
    float m_rotationAngle;
    SDL_Texture* m_objectTexture;
    vector<Gun*> m_guns;
    string m_bulletName;

    virtual void init(string configFile, coordinates coor, coordinates direction);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
    virtual void dealDamage(int damage);
    virtual void action();
protected:

private:
};

#endif // ENEMY_H
