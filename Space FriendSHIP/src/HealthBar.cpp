#include "HealthBar.h"

HealthBar::HealthBar()
{
    //ctor
}

HealthBar::~HealthBar()
{
    //dtor
    SDL_DestroyTexture(m_borderTexture);
    SDL_DestroyTexture(m_healthTexture);
}

void HealthBar::init(string configFile)
{
    m_configFile = "config//" + configFile;

    fstream stream;
    stream.open(m_configFile.c_str());
    stream >> m_objRect.w >> m_objRect.h >> m_objRect.x >> m_objRect.y >> m_borderFile >> m_healthImgFile;
    stream.close();
    m_borderFile = "img//" + m_borderFile;
    m_healthImgFile = "img//" + m_healthImgFile;

}
void HealthBar::update(int health, int maxHealth)
{
    HP = (float)health/(float)maxHealth;
}
void HealthBar::draw(SDL_Renderer* renderer)
{
    SDL_Surface* Loading_Surf = NULL;
    Loading_Surf = SDL_LoadBMP(m_borderFile.c_str());
    m_borderTexture = SDL_CreateTextureFromSurface(renderer, Loading_Surf);
    SDL_FreeSurface(Loading_Surf);

    Loading_Surf = SDL_LoadBMP(m_healthImgFile.c_str());
    m_healthTexture = SDL_CreateTextureFromSurface(renderer, Loading_Surf);
    SDL_FreeSurface(Loading_Surf);

    SDL_Rect m_barRect;
    m_barRect = m_objRect;
    m_barRect.w = m_objRect.w * HP;
    SDL_RenderCopy(renderer, m_borderTexture, NULL, &m_objRect);
    SDL_RenderCopy(renderer, m_healthTexture, NULL, &m_barRect);
}
