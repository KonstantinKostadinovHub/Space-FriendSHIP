#include "Shooter.h"

Shooter::Shooter()
{

}

Shooter::~Shooter()
{

}

void Shooter::init(string configFile, coordinates coor, float rotation, Enemy* enemy)
{
    Shooter* shooter = (Shooter*)enemy;

    m_objectRect = shooter -> m_objectRect;
    m_health = shooter -> m_health;
    m_collisonDamage = shooter -> m_collisonDamage;
    m_speed = shooter -> m_speed;
    m_attackSpeed = shooter -> m_attackSpeed;
    m_bulletName = shooter -> m_bulletName;
    m_pointsGiven = shooter -> m_pointsGiven;
    m_center = shooter -> m_center;
    m_objectTexture = shooter -> m_objectTexture;

    Gun* gun = new Gun;
    gun->init(m_attackSpeed);
    m_guns.push_back(gun);

    m_rotationAngle = rotation;
    m_objectRect.x = coor.x;
    m_objectRect.y = coor.y;
    m_coor.x = m_objectRect.x;
    m_coor.y = m_objectRect.y;
}

void Shooter::load(string configFile, SDL_Renderer* renderer)
{
    m_configFile = "config\\" + configFile;
    fstream stream;
    string tmp;

    stream.open(m_configFile.c_str());
    stream >> tmp >> m_objectRect.w >> m_objectRect.h;
    stream >> tmp >> m_img;
    stream >> tmp >> m_health;
    stream >> tmp >> m_collisonDamage;
    stream >> tmp >> m_attackSpeed;
    stream >> tmp >> m_speed;
    stream >> tmp >> m_bulletName;
    stream >> tmp >> m_pointsGiven;
    stream >> tmp >> m_center.x;
    stream.close();

    m_center.y = 0;

    m_img = "img\\" + m_img;

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
}
