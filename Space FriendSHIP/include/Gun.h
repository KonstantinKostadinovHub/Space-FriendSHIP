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
    float m_rotationAngle;

    time_t m_startShootCooldown;
    time_t m_shootCooldown;
    bool m_cantShoot;

    virtual void init(float attackSpeed);
    virtual void update(float playerAng, coordinates playerCoor);

protected:

private:
};

#endif // GUN_H
