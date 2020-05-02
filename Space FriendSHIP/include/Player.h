#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <chrono>
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
    string m_imgShield;

    coordinates m_oldCoor;
    coordinates m_coor;
    coordinates m_spawn;

    int m_dashLenght;
    int m_min_speed;
    int m_max_speed;
    int m_maxhealth;
    int m_health;

    float m_collisionDamage = 0;
    float m_speed;
    float m_screen_speed;

    bool m_canDash;
    bool m_hasCooldown;
    bool inDash;
    bool checkforShooting();
    bool m_canShoot;
    bool inShield = false;

    time_t m_startDashCooldown;
    time_t m_dashCooldown = 5;
    time_t m_startShootCooldown;
    time_t m_shootCooldown = 1;

    vector<Gun*> m_guns;

    string s_move_up;
    string s_move_down;
    string s_move_left;
    string s_move_right;
    string s_gas;
    string s_brake;
    string s_dash;
    string s_shoot;
    string m_bulletName = "bullet_player.txt";

    SDL_Scancode move_up;
    SDL_Scancode move_down;
    SDL_Scancode move_left;
    SDL_Scancode move_right;
    SDL_Scancode gas;
    SDL_Scancode brake;
    SDL_Scancode dash;
    SDL_Scancode shoot;

    SDL_Texture* m_shape1_tx = NULL;
    SDL_Surface* m_loading_surf = NULL;
    SDL_Texture* m_objectTexture;
    SDL_Texture* m_TextureWithShield;

    SDL_Rect m_objectRect;

    float m_rotationAngle;
    SDL_Point m_center;


    chrono::high_resolution_clock::time_point m_elapsed_engage;
    chrono::duration<float> m_engagementRate;

    virtual void init(SDL_Renderer* renderer, string configFile, UpgradeManager* upgradeManager);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
    virtual void checkForDash();

protected:

private:
};

#endif
