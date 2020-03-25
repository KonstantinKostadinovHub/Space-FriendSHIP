#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <SDL2/SDL.h>

#include "Engine.h"
#include "UpgradeManager.h"
#include "HealthBar.h"
#include "Gun.h"

using namespace std;

class Player
{
public:
    Player();
    virtual ~Player();

    HealthBar* m_healthBar;
    string HPBar;
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
    int m_maxhealth;
    int m_health;

    float m_collisionDamage;

    int m_dashLenght;
    bool m_canDash;
    bool m_hasCooldown;
    time_t m_startDashCooldown;
    time_t m_dashCooldown = 5;

    vector<Gun*> m_guns;

    string s_move_up;
    string s_move_down;
    string s_move_left;
    string s_move_right;
    string s_gas;
    string s_brake;
    string s_dash;

    string m_bulletName = "bullet_player.txt";

    SDL_Scancode move_up;
    SDL_Scancode move_down;
    SDL_Scancode move_left;
    SDL_Scancode move_right;
    SDL_Scancode gas;
    SDL_Scancode brake;
    SDL_Scancode dash;

    virtual void init(SDL_Renderer* renderer, string configFile, UpgradeManager* upgradeManager);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
    virtual void checkForDash();

    SDL_Texture* m_shape1_tx = NULL;
    SDL_Surface* m_loading_surf = NULL;
    SDL_Texture* m_objectTexture;
    SDL_Rect m_objectRect;

    float m_rotationAngle;
    SDL_Point m_center;

protected:

private:
};

#endif
