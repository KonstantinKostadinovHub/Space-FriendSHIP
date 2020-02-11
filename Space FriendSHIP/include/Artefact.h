#ifndef ARTEFACT_H
#define ARTEFACT_H
#include<SDL2/SDL.h>

class Artefact
{
    public:
        Artefact();
        virtual ~Artefact();

        virtual void update();
        virtual void draw(SDL_Renderer* renderer);
    protected:

    private:
};

#endif // ARTEFACT_H
