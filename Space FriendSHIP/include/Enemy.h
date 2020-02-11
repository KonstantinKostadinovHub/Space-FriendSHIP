#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <fstream>
#include <cstring>
#include<SDL2/SDL.h>

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
        int m_directionX;
        int m_directionY;
        float m_rotationAngle;
        SDL_Texture* m_objectTexture;

        virtual void init(string configFile, int x, int y);
        virtual void update();
        virtual void draw(SDL_Renderer* renderer);
        virtual void dealDamage(int damage);
    protected:

    private:
};

#endif // ENEMY_H
