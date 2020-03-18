#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Artefact.h"
#include "Player_AI.h"

#include "Engine.h"
#include "Spawner.h"
#include "Dropper.h"

#include "Rock.h"
#include "Shooter.h"
#include "ZigZag.h"

#include "Bullet.h"

using namespace std;

class World
{
public:
    World();
    virtual ~World();

    SDL_Window* m_main_window = NULL;
    SDL_Renderer* m_main_renderer = NULL;
    SDL_Texture* m_backgroundTexture;
    SDL_Rect m_ScreenR;
    SDL_Rect m_ScreenMenu;
    Spawner* m_spawnManager;
    Dropper* m_dropper;

    string m_configFile;
    string tmp;
    string m_backgroundImg;
    string m_endScreenImg;
    string m_menuImg;
    string m_menuImg1;
    string m_menuImg2;
    string m_menuImg3;

    int m_SCREEN_WIDTH;
    int m_SCREEN_HEIGHT;

    vector <Player*> m_players;
    vector <Enemy*> m_enemies;
    vector <Projectile*> m_projectiles;
    vector <Artefact*> m_artefacts;

    time_t m_startSpawnCooldown;
    time_t m_spawnCooldown;
    time_t m_startDropCooldown;
    time_t m_dropCooldown;

    bool m_spawn;
    bool endgame = false;
    bool m_drop;
    bool checkForCollisionBetweenObjects(SDL_Rect rect1, float angle1, SDL_Rect rect2, float angle2);
    bool checkIfOffBounds(SDL_Rect rect);

    void init(string configFile);
    void destroy();
    void update();
    void draw();
    void addPlayer(SDL_Renderer* renderer, string configFile);
    void collisionDamage();
    void addEnemy(string configFile, coordinates coor, float rotation);
    void addBullet(string configFile, coordinates coor, float rotation);
    void cleaner();
    void spawn();
    void endgameScreen();
    void menu();
    void shootProjectiles();
    void addArtefact(string configFile,coordinates coor, coordinates direction);
    void drop();

protected:

private:
};

#endif
