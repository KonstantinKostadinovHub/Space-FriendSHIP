#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "defines.h"

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
#include "Menu.h"
#include "SoundManager.h"
#include "Animation.h"
#include "Writer.h"

using namespace std;

class World
{
public:
    World();
    virtual ~World();

    SDL_Window* m_main_window = NULL;
    SDL_Renderer* m_main_renderer = NULL;

    SDL_Texture* m_backgroundTexture;
    SDL_Texture* m_bloodTexture1;
    SDL_Texture* m_bloodTexture2;
    SDL_Texture* m_bloodTexture3;
    SDL_Texture* m_tutorialTexture;
    SDL_Texture* m_backButtonTexture;
    SDL_Texture* m_titleImg1;
    SDL_Texture* m_titleImg2;

    SDL_Rect m_ScreenR;
    SDL_Rect m_ScreenMenu;
    SDL_Rect m_tutorialBackButton;

    Spawner* m_spawnManager;
    Dropper* m_dropper;
    UpgradeManager* m_upgradeManager;
    ConfigManager* m_configManager;
    Shop* m_shop;
    Menu* m_menu;
    SoundManager* m_soundManager;
    Writer* m_writer;

    string m_configFile;
    string tmp;
    string m_backgroundImg;
    string m_endScreenImg;
    string m_bloodImg1;
    string m_bloodImg2;
    string m_bloodImg3;
    string m_tutorialImg;
    string m_backButtonImg;
    string m_titleScreen1;
    string m_titleScreen2;

    int m_points;
    int m_highScore = 0;
    int m_coins;
    int m_enemiesPerSpawn;
    int m_wallet;
    int m_SCREEN_WIDTH;
    int m_SCREEN_HEIGHT;
    int mouseX, mouseY;
    int m_frameCount, m_timerFPS, m_lastFrame, m_fps;
    int m_lastTime = 0;

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
    bool m_mouseIsPressed;
    bool m_quitScene;

    SDL_Event m_event;
    GAME_STATE m_gameState;

    void init(string configFile);
    void destroy();
    void update();
    void draw();
    void input();
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
    void addAnimation(string configFile, coordinates coor,SDL_Renderer* renderer,float rotation,SDL_Point* center = NULL);
    void AddPoints(Enemy* enemy);
    void AddCoins(Enemy* enemy);
    void chooseGameMode();
    void endgameScreen();
    void saveProgress();
    void loadProgress();
    void shop();
    void destroySession();
    void initSession();
    void tutorial();
    void loadTitleScreen();
};

#endif
