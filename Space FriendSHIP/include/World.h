#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include<SDL2/SDL.h>

#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Artefact.h"

#include "Spawner.h"
#include "Engine.h"

#include "Rock.h"
#include "Bullet.h"

using namespace std;

class World
{
public:
    World();
    virtual ~World();

    SDL_Window* m_main_window = NULL;
    SDL_Renderer* m_main_renderer = NULL;
    SDL_Rect m_ScreenR;
    SDL_Rect m_ScreenMenu;

    bool endgame = false;
    string m_configFile;
    string m_endScreenImg="img\\EndGameScreen.bmp";
    string m_MenuImg="img\\MENU_unfinished1.bmp";
    int m_SCREEN_WIDTH;
    int m_SCREEN_HEIGHT;
    string m_backgroundImg;
    vector<Player*> m_players;
    vector<Enemy*> m_enemies;
    vector<Projectile*> m_projectiles;
    vector<Artefact*> m_artefacts;
    SDL_Texture* m_backgroundTexture;
    Spawner* m_spawnManager;
    time_t m_startSpawnCooldown;
    time_t m_spawnCooldown;
    bool m_spawn;

    void init(string configFile);
    void destroy();
    void update();
    void draw();
    void addEnemy(string configFile, coordinates coor, coordinates direction);
    void addBullet(string configFile, coordinates coor, coordinates direction);
    void cleaner();
    void spawn();
    bool checkForCollisionBetweenObjects(SDL_Rect rect1, SDL_Rect rect2);
    bool checkIfOffBounds(SDL_Rect rect);
    void endgameScreen();
    void menu();
    void shootProjectiles();
protected:

private:
};

#endif // WORLD_H
