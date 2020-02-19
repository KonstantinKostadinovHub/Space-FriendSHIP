#include "Gun.h"

Gun::Gun()
{
    //ctor
}

Gun::~Gun()
{
    //dtor
}

void Gun::init(coordinates coor)
{
    m_coor = coor;
}

void Gun::update(coordinates playerCoor, coordinates playerDirection, float rotation)
{

    m_objectRect.x = playerCoor.x + m_coor.x;
    m_objectRect.y = playerCoor.y + m_coor.y;
    struct coordinates buff;
    buff.x = 0;
    buff.y = 0;
    m_direction.x = playerDirection.x + buff.x;
    m_direction.y = playerDirection.y + buff.y;
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
