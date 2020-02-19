#ifndef GUN_H
#define GUN_H

#include <SDL2/Sdl.h>

#include "Engine.h"

class Gun
{
    public:
        Gun();
        virtual ~Gun();

        SDL_Rect m_objectRect;
        struct coordinates m_coor;
        struct coordinates m_direction;
        float m_rotationAngle;

        virtual void update(struct coordinates playerCoor, struct coordinates playerDirection, float playerAng);

    protected:

    private:
};

#endif // GUN_H
