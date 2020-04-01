#include "ZigZag.h"

ZigZag::ZigZag()
{
    m_rotatedUntilNow = 0;
    m_rotateRight = true;
}

ZigZag::~ZigZag()
{
    //dtor
}

void ZigZag::init(string configFile, coordinates coor, float rotation, ZigZag* zigzag)
{
    m_configFile = configFile;

    m_objectRect = zigzag -> m_objectRect;
    m_health = zigzag -> m_health;
    m_collisonDamage = zigzag -> m_collisonDamage;
    m_attackSpeed = zigzag -> m_attackSpeed;
    m_speed = zigzag -> m_speed;
    m_bulletName = zigzag -> m_bulletName;
    m_maxRotation = zigzag -> m_maxRotation;
    m_rotationFactor = zigzag -> m_rotationFactor;
    m_pointsGiven = zigzag -> m_pointsGiven;
    m_center = zigzag -> m_center;
    m_objectTexture = zigzag -> m_objectTexture;

    cout << "ZIG ZAG 30" << endl;

    m_rotationAngle = rotation;
    m_startRotation = rotation;
    m_objectRect.x = coor.x;
    m_objectRect.y = coor.y;
    m_coor.x = m_objectRect.x;
    m_coor.y = m_objectRect.y;
}

void ZigZag::update()
{
    if(m_rotateRight)
    {
        if(m_rotatedUntilNow < m_maxRotation)
        {
            m_rotatedUntilNow += m_rotationFactor;
        }
        else
        {
            m_rotateRight = false;
        }
    }
    else
    {
        if(m_rotatedUntilNow > -m_maxRotation)
        {
            m_rotatedUntilNow -= m_rotationFactor;
        }
        else
        {
            m_rotateRight = true;
        }
    }

    m_rotationAngle = m_startRotation + m_rotatedUntilNow;
    /* VERY GOOD BUG
    m_rotationAngle += m_rotatedUntilNow;
    */
    Enemy::update();
}

void ZigZag::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, m_rotationAngle, &m_center, SDL_FLIP_NONE);
}

void ZigZag::load(string configFile, SDL_Renderer* renderer)
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
    stream >> tmp >> m_maxRotation;
    stream >> tmp >> m_rotationFactor;
    stream >> tmp >> m_pointsGiven;
    stream >> tmp >> m_center.x;
    stream.close();

    m_center.y = 0;

    Gun* gun = new Gun;
    gun->init(m_attackSpeed);
    m_guns.push_back(gun);

    m_img = "img\\" + m_img;

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
}
