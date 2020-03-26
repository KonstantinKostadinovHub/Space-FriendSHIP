#include "Artefact.h"

Artefact::Artefact()
{
    m_frameCounter = 0;
    m_startCounter = time(NULL);
}

Artefact::~Artefact()
{
    //dtor
}

void Artefact::update()
{
    m_coor.x += (m_direction.x * m_speed * SPEED_FACTOR);
    m_coor.y += (m_direction.y * m_speed * SPEED_FACTOR);
    m_objectRect.x = (int)m_coor.x;
    m_objectRect.y = (int)m_coor.y;
}

void Artefact::init(string configFile, coordinates coor, coordinates direction,SDL_Renderer* renderer)
{

    m_configFile = "config\\" + configFile;
    fstream stream;
    stream.open(m_configFile.c_str());

    stream >> tmp >> m_objectRect.w >> m_objectRect.h;
    stream >> tmp >> m_img;
    stream >> tmp >> m_speed;
    stream >> tmp >> m_FrameCount;
    stream >> tmp >> m_actionEffect;
    stream.close();

    m_direction.x = direction.x;
    m_direction.y = direction.y;
    m_objectRect.x = coor.x;
    m_objectRect.y = coor.y;
    m_img = "img\\" + m_img;
    m_coor.x = m_objectRect.x;
    m_coor.y = m_objectRect.y;

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);

}

void Artefact::draw( SDL_Renderer* renderer)
{

    SDL_Rect pictureRect;
    pictureRect.x = 0;
    pictureRect.y = m_objectRect.h * m_frameCounter;
    pictureRect.w = m_objectRect.w;
    pictureRect.h = m_objectRect.h;
    m_frameCounter++;

    if(m_startCounter + m_FrameCooldown < time(NULL))
    {
        m_startCounter = time(NULL);
        m_frameCounter ++;
    }
    if(m_frameCounter > m_FrameCount - 1)
    {
        m_frameCounter = 0;
    }
    SDL_RenderCopy(renderer, m_objectTexture, &pictureRect, &m_objectRect);

}
