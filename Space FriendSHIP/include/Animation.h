#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL2/SDL.h>
#include <fstream>
#include <ctime>
#include "Engine.h"

class Animation
{
public:
    coordinates m_coor;
    coordinates m_direction;
    SDL_Rect m_objectRect;
    SDL_Rect m_SpriteRect;
    SDL_Texture* m_objectTexture;
    SDL_Rect m_Animation;
    string m_img;
    string tmp;
    float m_actionEffect;
    int m_health = 2;
    int m_frameCounter;
    time_t m_startCounter;
    time_t m_FrameCooldown;
    int m_FrameCount;
    string m_configFile;
    bool finished= false;
    float m_rotationAngle;
    SDL_Point m_center;

    Animation();
    virtual ~Animation();
    virtual void init(string configFile, coordinates coor,SDL_Renderer* renderer,float rotation,SDL_Point* center);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
protected:

private:
};

#endif // ANIMATION_H
