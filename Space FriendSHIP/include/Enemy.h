#ifndef ENEMY_H
#define ENEMY_H
#include<SDL2/SDL.h>


class Enemy
{
    public:
        Enemy();
        virtual ~Enemy();

        virtual void update();
        virtual void draw(SDL_Renderer* renderer);
    protected:

    private:
};

#endif // ENEMY_H
