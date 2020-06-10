#include "Animation.h"

Animation::Animation()
{

}

Animation::~Animation()
{

}

void Animation::init(string configFile, coordinates coor,SDL_Renderer* renderer,float rotation,SDL_Point* center)
{

    m_configFile = "config\\" + configFile;

    m_frameCounter = 0;

    fstream stream;
    string tmp;

    stream.open(m_configFile.c_str());
    stream >> tmp >> m_objectRect.w >> m_objectRect.h;
    stream >> tmp >> m_img;
    stream >> tmp >> m_FrameCount;
    stream >> tmp >> m_FrameCooldown;
    stream.close();

    if(center != NULL)
    {
        m_center = *center;
    }

    m_rotationAngle = rotation;
    m_objectRect.x = coor.x;
    m_objectRect.y = coor.y;
    m_img = "img\\" + m_img;
    m_coor.x = m_objectRect.x;
    m_coor.y = m_objectRect.y;

    m_startCounter = time(NULL);

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
}

void Animation::update()
{

}

void Animation::draw(SDL_Renderer* renderer)
{
    SDL_Rect pictureRect;
    pictureRect.x = m_objectRect.h * m_frameCounter;
    pictureRect.y = 0;
    pictureRect.w = m_objectRect.w;
    pictureRect.h = m_objectRect.h;
    m_frameCounter ++;

    if(m_startCounter + m_FrameCooldown < time(NULL))
    {
        m_startCounter = time(NULL);
    }
    if(m_frameCounter > m_FrameCount-1)
    {
        finished=true;

    }
    SDL_RenderCopyEx(renderer, m_objectTexture, &pictureRect, &m_objectRect, m_rotationAngle, &m_center, SDL_FLIP_NONE);
}
