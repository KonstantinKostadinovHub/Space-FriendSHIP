#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::init(string configFile, coordinates coor, coordinates direction)
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
}

void Enemy::update()
{
    m_coor.x += (m_direction.x * m_speed);
    m_coor.y += (m_direction.y * m_speed);
    m_objectRect.x = (int)m_coor.x;
    m_objectRect.y = (int)m_coor.y;
}

void Enemy::draw(SDL_Renderer* renderer)
{
    float tanges = m_direction.y / m_direction.x;
    //cout << "tanges:" << tanges << " result:";
    float result = 0;
    if (m_direction.y < 0 && abs(m_direction.y) > abs(m_direction.x))
    {
        tanges =  m_direction.x / m_direction.y;
        tanges = abs(tanges);
        result = tan(tanges) * 180 / PI;
    }
    else if ( m_direction.y > 0 && abs(m_direction.y) > abs(m_direction.x))
    {
        tanges = m_direction.x / m_direction.y;
        tanges = abs(tanges);
        result = 180 - tan(tanges) * 180 / PI;
    }
    else if ( abs(m_direction.y) < abs(m_direction.x))
    {
        tanges = m_direction.y / m_direction.x;
        tanges = abs(tanges);
        if(m_direction.y > 0)
        {
            result = tan(tanges) * 180 /PI + 90;
        }
        else
        {
            result = 90 - tan(tanges) * 180 / PI;
        }
    }
    if (m_direction.x < 0)
    {
        result *= -1;
    }
    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, result, NULL, SDL_FLIP_NONE);
    SDL_FreeSurface(loadingSurface);

    for(int i = 0; i < m_guns.size() ; i++)
    {
        struct coordinates buff;
        buff.x = m_objectRect.x;
        buff.y = m_objectRect.y;
        // TO - DO hardcoded
        m_guns[i]->update(buff, m_direction, 0);
    }
}

void Enemy::dealDamage(int damage)
{
    m_health -= damage;
}

void Enemy::action()
{

}
