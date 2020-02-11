#ifndef PLAYER_H
#define PLAYER_H
#include<SDL2/SDL.h>

class Player
{
    public:
        Player();
        virtual ~Player();

        virtual void update();
        virtual void draw(SDL_Renderer* renderer);
    protected:

    private:
};

#endif // PLAYER_H
