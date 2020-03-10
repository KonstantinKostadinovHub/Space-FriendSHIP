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
    m_objectRect.x = playerCoor.x + (m_coor.x * 19);
    m_objectRect.y = playerCoor.y - (m_coor.y * 49);

    m_coor = returnCoordinatesByAngle(rotation);
    m_rotationAngle = rotation;

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
