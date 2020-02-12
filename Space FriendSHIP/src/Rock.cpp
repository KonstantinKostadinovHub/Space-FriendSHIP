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
    m_objectRect.x += (int)(m_directionX * m_speed);
    m_objectRect.y += (int)(m_directionY * m_speed);
    m_buffX += (float)(m_directionX * m_speed) - (int)(m_directionX * m_speed);
    m_buffY += (float)(m_directionY * m_speed) - (int)(m_directionY * m_speed);
    if(abs(m_buffX) > 1){
        m_objectRect.x += (int)m_buffX;
        m_buffX -= (int)m_buffX;
    }
    if(abs (m_buffY) > 1){
        m_objectRect.y += (int)m_buffY;
        m_buffY -= (int)m_buffY;
    }
}
