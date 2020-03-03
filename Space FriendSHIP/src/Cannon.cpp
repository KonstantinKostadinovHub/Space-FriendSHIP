#include "Cannon.h"

Cannon::Cannon()
{
    //ctor
}

Cannon::~Cannon()
{
    //dtor
}

void Cannon::getPlayerCoor(coordinates playerCoor)
{
    m_playerCoor = playerCoor;
}

void Cannon::update()
{
    m_direction.x = m_playerCoor.x - m_objectRect.x;
    m_direction.y = m_playerCoor.y - m_objectRect.y;

    if(m_direction.x > m_direction.y)
    {
        m_direction.y = m_direction.x / m_direction.y;
        m_direction.x = m_direction.x > 0 ? m_direction.x = 1 : m_direction.x = -1;
    }
    if(m_direction.y > m_direction.x)
    {
        m_direction.x = m_direction.y / m_direction.x;
        m_direction.y = m_direction.y > 0 ? m_direction.y = 1 : m_direction.y = -1;
    }
    for(int i = 0; i < m_guns.size() ; i++)
    {
        struct coordinates objCoor;
        objCoor.x = m_objectRect.x;
        objCoor.y = m_objectRect.y;
        m_guns[i]->update(objCoor, m_rotationAngle, 90);
    }
}

void Cannon::init(string configFile, coordinates coor, coordinates direction)
{
    m_configFile = "config\\" + configFile;
    fstream stream;
    stream.open(m_configFile.c_str());
    stream >> m_objectRect.w >> m_objectRect.h >> m_img >> m_health >>m_collisonDamage >> m_attackSpeed >> m_speed;
    stream.close();

    m_direction.x = direction.x;
    m_direction.y = direction.y;
    m_objectRect.x = coor.x;
    m_objectRect.y = coor.y;
    m_img = "img\\" + m_img;
    m_coor.x = m_objectRect.x;
    m_coor.y = m_objectRect.y;

    Gun* gun = new Gun();
    gun->init(coor);
    m_guns.push_back(gun);
}
