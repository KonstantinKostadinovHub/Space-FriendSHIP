#include "Enemy.h"

Enemy::Enemy()
{
    m_buff.x = 0;
    m_buff.y = 0;
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
}

void Enemy::update()
{

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
        //cout << tan(tanges) * 180 / PI << " " << endl;
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
    //cout << "result: " << result << endl;
    //result += 180;
    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, result, NULL, SDL_FLIP_NONE);
    SDL_FreeSurface(loadingSurface);
}

void Enemy::dealDamage(int damage)
{
    m_health -= damage;
}

void Enemy::action()
{

}
