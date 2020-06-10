#include "Gun.h"

Gun::Gun()
{

}

Gun::~Gun()
{

}

void Gun::init(float attackSpeed)
{
    m_engagementRate = chrono::milliseconds((int)attackSpeed);
    m_elapsed_engage = chrono::high_resolution_clock::now();
    m_cantShoot = true;
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
        m_elapsed_engage = chrono::high_resolution_clock::now();
    }
    else if(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_elapsed_engage) > m_engagementRate)
    {
        m_cantShoot = false;
    }
}
