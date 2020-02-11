#ifndef PROJECTILE_H
#define PROJECTILE_H
#include<SDL2/SDL.h>

class Projectile
{
    public:
        Projectile();
        virtual ~Projectile();

        virtual void update();
        virtual void draw(SDL_Renderer* renderer);
    protected:

    private:
};

#endif // PROJECTILE_H
