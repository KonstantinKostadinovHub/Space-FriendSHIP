#ifndef ARTEFACT_H
#define ARTEFACT_H
#include <SDL2/SDL.h>
#include <fstream>
#include <ctime>
#include "Engine.h"

class Artefact
{
public:
    coordinates m_coor;
    coordinates m_direction;
    SDL_Rect m_objectRect;
    SDL_Rect m_SpriteRect;
    SDL_Texture* m_objectTexture;
    SDL_Rect m_Artefact;
    string m_img;
    string m_type;
    string tmp;
    float m_actionEffect;
    float m_speed ;
    int m_health = 2;
    int m_frameCounter;
    time_t m_startCounter;
    time_t m_FrameCooldown;
    int m_FrameCount;
    //mustn't be hardcoded
    Artefact();
    virtual ~Artefact();
    string m_configFile;
    virtual void init(string configFile, coordinates coor, coordinates direction,SDL_Renderer* renderer);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
protected:

private:
};

#endif // ARTEFACT_H
