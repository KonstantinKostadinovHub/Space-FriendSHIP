#ifndef GUN_H
#define GUN_H

#include <time.h>

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

        time_t m_startShootCooldown;
        time_t m_shootCooldown;
        bool m_cantShoot;

        virtual void init(coordinates coor);
        virtual void update(coordinates playerCoor, coordinates playerDirection, float playerAng);

    protected:

    private:
};

#endif // GUN_H
