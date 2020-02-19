#include "Gun.h"

Gun::Gun()
{
    //ctor
}

Gun::~Gun()
{
    //dtor
}

void Gun::update(struct coordinates playerCoor, struct coordinates playerDirection, float playerAng)
{
    m_coor.x = playerCoor.x + m_coor.x;
    m_coor.y = playerCoor.y + m_coor.y;
    m_direction.x = playerDirection.x;
    m_direction.y = playerDirection.y;
    m_rotationAngle = playerAng;
}
