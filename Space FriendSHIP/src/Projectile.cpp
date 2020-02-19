#include "Projectile.h"

Projectile::Projectile()
{
    //ctor
}

Projectile::~Projectile()
{
    //dtor
}
void Projectile::update()
{
    m_coor.x += m_direction.x*m_speed;
    m_coor.y += m_direction.y*m_speed;
    m_objectRect.x = (int)m_coor.x;
    m_objectRect.y = (int)m_coor.y;
}

void Projectile::draw(SDL_Renderer* renderer)
{
    float m_rotationAngle = returnAngleByCoordinates(m_coor, m_direction);

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, m_rotationAngle, NULL, SDL_FLIP_NONE);
}

void Projectile::init(string configFile, struct coordinates coor, struct coordinates direction)
{
    m_configFile = "config\\" + configFile;
    fstream stream;
    stream.open(m_configFile.c_str());
    stream >> m_objectRect.w >> m_objectRect.h>>m_health>>m_speed>>m_collisonDamage>>m_img;
    stream.close();
    m_coor.x = coor.x;
    m_coor.y = coor.y;
    m_direction.x = direction.x;
    m_direction.y = direction.y;
    m_img = "img\\" + m_img;
}
