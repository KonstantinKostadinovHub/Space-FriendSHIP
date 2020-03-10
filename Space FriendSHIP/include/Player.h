#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <cmath>
#include "Engine.h"

using namespace std;

class Player
{
public:
    Player();
    virtual ~Player();

    string m_playerImage;
    string m_configFile;
    string m_img;
    string tmp;

    int m_spawn_x;
    int m_spawn_y;
    float m_speed;
    float m_screen_speed;
    int m_min_speed;
    int m_max_speed;
    int m_health;

    string s_move_up;
    string s_move_down;
    string s_move_left;
    string s_move_right;
    string s_gas;
    string s_brake;

    SDL_Scancode move_up;
    SDL_Scancode move_down;
    SDL_Scancode move_left;
    SDL_Scancode move_right;
    SDL_Scancode gas;
    SDL_Scancode brake;

    virtual void init(SDL_Renderer* renderer, string configFile);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);

    SDL_Texture* m_shape1_tx = NULL;
    SDL_Surface* m_loading_surf = NULL;
    SDL_Texture* m_objectTexture;
    SDL_Rect m_objectRect;

    float m_rotationAngle;

protected:

private:
};

#endif
