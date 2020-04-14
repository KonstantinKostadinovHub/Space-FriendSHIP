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

#include "Rock.h"
#include "Shooter.h"
#include "ZigZag.h"

#include "Bullet.h"

#include "Engine.h"
#include "Spawner.h"
#include "Dropper.h"
#include "UpgradeManager.h"
#include "ConfigManager.h"
#include "Shop.h"
#include "SoundManager.h"
#include "Animation.h"

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
    UpgradeManager* m_upgradeManager;
    ConfigManager* m_configManager;
    Shop* m_shop;

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

    int mouseX, mouseY;
    bool mouseIsPressed;

    int m_points;
    int m_highScore;
    int m_coins;

    vector <Player*> m_players;
    vector <Enemy*> m_enemies;
    vector <Projectile*> m_projectiles;
    vector <Artefact*> m_artefacts;
    vector <Animation*> m_animations;

    time_t m_startSpawnCooldown;
    time_t m_spawnCooldown;
    time_t m_startDropCooldown;
    time_t m_dropCooldown;

    bool m_spawn;
    bool endgame = false;
    bool m_drop;
    bool checkForCollisionBetweenObjects(SDL_Rect rect_no_rotation1, float angle1, SDL_Point* center1,
                                         SDL_Rect rect_no_rotation2, float angle2, SDL_Point* center2);
    bool checkIfOffBounds(SDL_Rect rect);

    int m_wallet;

    void init(string configFile);
    void destroy();
    void update();
    void draw();
    void collisionDamage();
    void cleaner();
    void shootProjectiles();
    void spawn();
    void drop();
    void addEnemy(string configFile, coordinates coor, float rotation);
    void addBullet(string configFile, coordinates coor, float rotation);
    void addArtefact(string configFile,coordinates coor, coordinates direction);
    void addPlayer(SDL_Renderer* renderer, string configFile);
    void addPlayerAI(SDL_Renderer* renderer, string configFile);
    void AddPoints(Enemy* enemy);
    void AddCoins (Enemy* enemy);
    void chooseGameMode();
    void menu();
    void endgameScreen();
    void saveProgress();
    void loadProgress();
    void shop();
    void addAnimation(string configFile, coordinates coor,SDL_Renderer* renderer,float rotation,SDL_Point* center = NULL);


protected:

private:
};

#endif
