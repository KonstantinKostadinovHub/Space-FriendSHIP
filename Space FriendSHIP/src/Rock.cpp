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
    m_objectRect.x += (int)(m_direction.x * m_speed);
    m_objectRect.y += (int)(m_direction.y * m_speed);
    m_buff.x += (float)(m_direction.x * m_speed) - (int)(m_direction.x * m_speed);
    m_buff.y += (float)(m_direction.y * m_speed) - (int)(m_direction.y * m_speed);
    if(abs(m_buff.x) > 1)
    {
        m_objectRect.x += (int)m_buff.x;
        m_buff.x -= (int)m_buff.x;
    }
    if(abs (m_buff.y) > 1)
    {
        m_objectRect.y += (int)m_buff.y;
        m_buff.y -= (int)m_buff.y;
    }
}
