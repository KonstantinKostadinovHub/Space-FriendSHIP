#include "Rock.h"

Rock::Rock()
{
    //ctor
}

Rock::~Rock()
{
    //dtor
}

void Rock::update()
{
    m_objectRect.x += m_directionX * m_speed;
    m_objectRect.y += m_directionY * m_speed;
}
