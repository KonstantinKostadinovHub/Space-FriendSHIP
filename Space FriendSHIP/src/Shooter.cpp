#include "Shooter.h"

Shooter::Shooter()
{
    //ctor
}

Shooter::~Shooter()
{
    //dtor
}

void Shooter::init(string configFile, coordinates coor, float rotation, SDL_Renderer* renderer)
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
    stream >> tmp >> m_bulletName;
    stream >> tmp >> m_pointsGiven;
    stream >> tmp >> m_center.x;
    stream.close();

    m_rotationAngle = rotation;
    m_objectRect.x = coor.x;
    m_objectRect.y = coor.y;
    m_img = "img\\" + m_img;
    m_coor.x = m_objectRect.x;
    m_coor.y = m_objectRect.y;

    m_center.y = 0;

    Gun* gun = new Gun;
    gun->init(m_attackSpeed);
    m_guns.push_back(gun);

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
}
