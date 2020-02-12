#include "Enemy.h"

Enemy::Enemy()
{
    m_buffX = 0;
    m_buffY = 0;
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::init(string configFile, int x, int y, float directionX, float directionY)
{
    m_configFile = "config\\" + configFile;
    fstream stream;
    stream.open(m_configFile.c_str());
    stream >> m_objectRect.w >> m_objectRect.h >> m_img >> m_health >>m_collisonDamage >> m_attackSpeed >> m_speed;
    stream.close();

    m_directionX = directionX;
    m_directionY = directionY;
    m_objectRect.x = x;
    m_objectRect.y = y;
    m_img = "img\\" + m_img;
}

void Enemy::update()
{

}

void Enemy::draw(SDL_Renderer* renderer)
{
    float tanges = m_directionY / m_directionX;
    //cout << "tanges:" << tanges << " result:";
    float result = 0;
    if (m_directionY < 0 && abs(m_directionY) > abs(m_directionX))
    {
        tanges =  m_directionX / m_directionY;
        tanges = abs(tanges);
        result = tan(tanges) * 180 / PI;
    } else if ( m_directionY > 0 && abs(m_directionY) > abs(m_directionX))
    {
        tanges = m_directionX / m_directionY;
        tanges = abs(tanges);
        result = 180 - tan(tanges) * 180 / PI;
    } else if ( abs(m_directionY) < abs(m_directionX))
    {
        tanges = m_directionY / m_directionX;
        tanges = abs(tanges);
        //cout << tan(tanges) * 180 / PI << " " << endl;
        if(m_directionY > 0)
        {
            result = tan(tanges) * 180 /PI + 90;
        } else {
            result = 90 - tan(tanges) * 180 / PI;
        }
    }
    if (m_directionX < 0)
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
