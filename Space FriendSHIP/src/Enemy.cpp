#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::init(string configFile, coordinates coor, float rotation, SDL_Renderer* renderer)
{
    m_configFile = "config\\" + configFile;

    fstream stream;
    stream.open(m_configFile.c_str());
    stream >> tmp >> m_objectRect.w >> m_objectRect.h;
    stream >> tmp >> m_img;
    stream >> tmp >> m_health;
    stream >> tmp >> m_collisonDamage;
    stream >> tmp >> m_attackSpeed;
    stream >> tmp >> m_speed;
    stream >> tmp >> m_pointsGiven;
    stream.close();

    m_rotationAngle = rotation;
    m_objectRect.x = coor.x;
    m_objectRect.y = coor.y;
    m_img = "img\\" + m_img;
    m_coor.x = m_objectRect.x;
    m_coor.y = m_objectRect.y;

    m_center.x = m_objectRect.w/2;
    m_center.y = 0;

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
}

void Enemy::update()
{
    m_coor.x += (sin(m_rotationAngle * PI / 180) * m_speed * SPEED_FACTOR);
    m_coor.y -= (cos(m_rotationAngle * PI / 180) * m_speed * SPEED_FACTOR);
    m_objectRect.x = (int)m_coor.x;
    m_objectRect.y = (int)m_coor.y;

    for(int i = 0; i < m_guns.size() ; i++)
    {
        coordinates playerCoor;
        playerCoor.x = m_objectRect.x;
        playerCoor.y = m_objectRect.y;
        m_guns[i] -> update(m_rotationAngle, playerCoor);
    }
}

void Enemy::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, m_rotationAngle, &m_center, SDL_FLIP_NONE);
}

void Enemy::dealDamage(int damage)
{
    m_health -= damage;
}

void Enemy::action()
{

}
