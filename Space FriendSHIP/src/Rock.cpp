#include "Rock.h"

Rock::Rock()
{
    //ctor
}

Rock::~Rock()
{
    //dtor
}

void Rock::init(string configFile, coordinates coor, coordinates direction)
{
    m_configFile = "config\\" + configFile;
    fstream stream;
    stream.open(m_configFile.c_str());
    stream >> m_objectRect.w >> m_objectRect.h >> m_img >> m_health >>m_collisonDamage >> m_attackSpeed >> m_speed;
    stream.close();
    m_bulletName = "bullet.txt";

    Gun* gun = new Gun;
    struct coordinates buff;
    buff.x = 0;
    buff.y = 50;
    gun->init(buff);
    m_guns.push_back(gun);
    m_direction.x = direction.x;
    m_direction.y = direction.y;
    m_objectRect.x = coor.x;
    m_objectRect.y = coor.y;
    m_coor.x = m_objectRect.x;
    m_coor.y = m_objectRect.y;
    m_img = "img\\" + m_img;
}
