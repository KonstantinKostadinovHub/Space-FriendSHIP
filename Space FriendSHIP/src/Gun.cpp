#include "Gun.h"

Gun::Gun()
{
    //ctor
}

Gun::~Gun()
{
    //dtor
}

void Gun::init(float attackSpeed)
{
    m_shootCooldown = attackSpeed;
}

void Gun::update(float rotation, coordinates playerCoor)
{
    coordinates bulletCoor = returnCoordinatesByAngle(rotation);
    m_rotationAngle = rotation;

    int sign = (bulletCoor.y > 0 ? 1: -1);

    m_objectRect.x = playerCoor.x;
    m_objectRect.y = playerCoor.y - sign*(bulletCoor.y * 8);

    if(!m_cantShoot)
    {
        m_cantShoot = true;
        m_startShootCooldown = time(NULL);
    }
    else if(m_startShootCooldown + m_shootCooldown < time(NULL))
    {
        m_cantShoot = false;
    }
}
