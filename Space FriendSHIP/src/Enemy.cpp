#include "Enemy.h"

Enemy::Enemy()
{
    m_rotationAngle = 0;
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::init(string configFile, int x, int y)
{
    m_configFile = "config\\" + configFile;
    fstream stream;
    stream.open(m_configFile.c_str());
    stream >> m_objectRect.w >> m_objectRect.h >> m_img >> m_health >>m_collisonDamage >> m_attackSpeed >> m_speed;
    stream.close();

    m_objectRect.x = x;
    m_objectRect.y = y;
    m_img = "img\\" + m_img;
}

void Enemy::update()
{

}

void Enemy::draw(SDL_Renderer* renderer)
{
    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, m_rotationAngle, NULL, SDL_FLIP_NONE);
    SDL_FreeSurface(loadingSurface);
}

void Enemy::dealDamage(int damage)
{
    m_health -= damage;
}
