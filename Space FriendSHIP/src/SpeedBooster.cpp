#include "SpeedBooster.h"

SpeedBooster::SpeedBooster()
{
    //ctor
}

SpeedBooster::~SpeedBooster()
{
    //dtor
}

void SpeedBooster::init(string configFile, coordinates coor, coordinates direction)
{
    m_configFile = "config\\" + configFile;
    fstream stream;
    stream.open(m_configFile.c_str());
    stream >> tmp >> m_objectRect.w >> m_objectRect.h;
    stream >> tmp >> m_img;
    stream >> tmp >> m_speed;

    stream.close();

    m_direction.x = direction.x;
    m_direction.y = direction.y;
    m_objectRect.x = coor.x;
    m_objectRect.y = coor.y;
    m_coor.x = m_objectRect.x;
    m_coor.y = m_objectRect.y;
    m_img = "img\\" + m_img;
}
